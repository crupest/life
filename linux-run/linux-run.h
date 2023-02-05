#ifndef LINUX_RUN_H
#define LINUX_RUN_H

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

namespace linux_run {

enum StopReason { Exited, Killed };

struct RunOptions {
  RunOptions()
      : timeout_in_second(0), check_exit_code(true), stop_reason(nullptr),
        exit_code(nullptr) {}

  int timeout_in_second;
  bool check_exit_code;
  std::string stdin_file_path;
  std::string stdout_file_path;
  StopReason *stop_reason;
  int *exit_code;
  // Before reap so you can get final information of the process.
  std::function<void(int pid)> before_reap_callback;
};

class TimeoutError : std::runtime_error {
public:
  using runtime_error::runtime_error;
};

class ExitCodeError : std::runtime_error {
public:
  using runtime_error::runtime_error;
};

void run(const std::string &program, std::vector<std::string> arguments,
         RunOptions options);

} // namespace linux_run

#endif
