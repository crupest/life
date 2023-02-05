#include "linux-run.h"

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <string.h> // for strerror_r (GNU extension)
#include <sys/signalfd.h>
#include <sys/wait.h>
#include <unistd.h>

namespace linux_run {
static std::string get_errno_message() {
  char buffer[100];
  strerror_r(errno, buffer, 100);
  return std::string(buffer);
}

static std::string get_errno_message(int custom_errno) {
  char buffer[100];
  strerror_r(custom_errno, buffer, 100);
  return std::string(buffer);
}

static void create_signal_fd(int *pfd) {
  sigset_t sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGCHLD);
  if (sigprocmask(SIG_BLOCK, &sigset, nullptr) == -1) {
    throw std::runtime_error("Failed to block SIGCHLD. Reason: " +
                             get_errno_message());
  }

  sigemptyset(&sigset);
  sigaddset(&sigset, SIGCHLD);
  int fd = signalfd(-1, &sigset, 0);
  if (fd == -1) {
    throw std::runtime_error("Failed to create SIGCHLD fd. Reason: " +
                             get_errno_message());
  }
  *pfd = fd;
}

static void destroy_signal_fd(int fd) {
  if (close(fd) == -1) {
    throw std::runtime_error("Failed to close SIGCHLD fd. Reason: " +
                             get_errno_message());
  }

  sigset_t sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGCHLD);
  if (sigprocmask(SIG_UNBLOCK, &sigset, nullptr) == -1) {
    throw std::runtime_error("Failed to unblock SIGCHLD. Reason: " +
                             get_errno_message());
  }
}

static char **
convert_string_vector_to_argv(const std::string &program,
                              const std::vector<std::string> &arguments) {
  char **argv;
  argv = new char *[arguments.size() + 2];
  argv[0] = new char[program.size() + 1];
  strcpy(argv[0], program.c_str());
  for (int i = 0; i < arguments.size(); i++) {
    const auto &argument = arguments[i];
    argv[i + 1] = new char[argument.size() + 1];
    strcpy(argv[i + 1], argument.c_str());
  }
  argv[arguments.size() + 1] = nullptr;
  return argv;
}

static void redirect_file(int old_file_descriptor, const std::string &path,
                          int open_file_flags) {
  if (path.empty())
    return;
  int file_descriptor = open(path.c_str(), open_file_flags);
  if (file_descriptor == -1)
    throw std::runtime_error(
        "Failed to open " + path +
        " for redirection. Reason: " + get_errno_message());
  int dup_r = dup2(file_descriptor, old_file_descriptor);
  if (dup_r == -1)
    throw std::runtime_error(
        "Failed to dup file descriptor for redirection. Reason: " +
        get_errno_message());
  int close_r = close(file_descriptor);
  if (close_r == -1)
    throw std::runtime_error(
        "Failed to close old file descriptor for redirection. Reason: " +
        get_errno_message());
}

void run(const std::string &program, std::vector<std::string> arguments,
         RunOptions options) {

  int sigchld_fd;
  create_signal_fd(&sigchld_fd);

  pid_t pid = fork();
  if (pid == 0) {
    destroy_signal_fd(sigchld_fd);

    redirect_file(STDIN_FILENO, options.stdin_file_path, O_RDONLY);
    redirect_file(STDOUT_FILENO, options.stdout_file_path,
                  O_WRONLY | O_CREAT | O_TRUNC);
    auto argv = convert_string_vector_to_argv(program, arguments);
    int r = execvp(program.c_str(), argv);
    throw std::runtime_error("Failed to exec: " + get_errno_message());
  }
  if (pid == -1) {
    throw std::runtime_error("Failed to fork: " + get_errno_message());
  }

  struct pollfd sigchld_poll;
  sigchld_poll.fd = sigchld_fd;
  sigchld_poll.events = POLLIN;
  sigchld_poll.revents = 0;

  int timeout_value =
      options.timeout_in_second > 0 ? options.timeout_in_second * 1000 : -1;

  while (true) {
    int poll_return = poll(&sigchld_poll, 1, timeout_value);

    if (poll_return == 0) {
      throw TimeoutError("Timeout to run command.");
    } else if (poll_return == -1) {
      if (errno == EINTR) {
        continue;
      } else {
        throw std::runtime_error("Failed to poll. Reason: " +
                                 get_errno_message());
      }
    } else if (poll_return == 1) {
      break;
    } else {
      throw std::runtime_error("Poll returns a wired value.");
    }
  }

  signalfd_siginfo sig_info;

  if (sigchld_poll.revents & POLLIN) {
    size_t read_size = sizeof(signalfd_siginfo);
    int read_return = read(sigchld_fd, &sig_info, read_size);
    if (read_return == -1) {
      throw std::runtime_error("Failed to read signal fd. Reason: " +
                               get_errno_message());
    } else if (read_return != read_size) {
      throw std::runtime_error("Failed to read signal fd because the return "
                               "byte count does not match request.");
    }
  } else {
    throw std::runtime_error("SIGCHLD fd is not readable after poll.");
  }

  switch (sig_info.ssi_code) {
  case CLD_EXITED: {
    if (options.stop_reason) {
      *options.stop_reason = StopReason::Exited;
    }
    int exit_code = sig_info.ssi_status;
    if (options.exit_code) {
      *options.exit_code = exit_code;
    }
    if (options.check_exit_code) {
      if (exit_code != 0) {
        throw ExitCodeError("Command exit with nonzero value.");
      }
    }
  } break;
  case CLD_KILLED: {
    if (options.stop_reason) {
      *options.stop_reason = StopReason::Killed;
    }
  } break;
  default:
    throw std::runtime_error("Unsupported sig_info code.");
  }

  if (options.before_reap_callback) {
    options.before_reap_callback(pid);
  }

  // Reap child.
  if (waitpid(pid, nullptr, 0) == -1) {
    throw std::runtime_error("Failed to reap child process. Reason: " +
                             get_errno_message());
  }
}

} // namespace linux_run
