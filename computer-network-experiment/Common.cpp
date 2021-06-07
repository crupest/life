#include "Common.h"

#include "Output.h"

#ifdef WIN32
#include <Windows.h>
#include <winsock.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#endif

#include <string>

[[noreturn]] void PrintErrorMessageAndExit(StringView message,
                                           bool print_last_error) {

  SendOutput(CRUT("{}\n"), message);

  if (print_last_error) {
#ifdef WIN32
    auto error_code = WSAGetLastError();
    SendOutput(OutputType::Error, CRUT("Error code is {}.\n"), error_code);
    wchar_t buffer[500];
    if (!FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
                            FORMAT_MESSAGE_ARGUMENT_ARRAY |
                            FORMAT_MESSAGE_IGNORE_INSERTS,
                        nullptr, error_code, 0, buffer, 500, nullptr)) {
      SendOutput(OutputType::Error, CRUT("Failed to format error message.\n"));
    } else {
      SendOutput(OutputType::Error, CRUT("{}\n"), buffer);
    }
#else
#endif
  }

  BeforeExit();

  std::exit(1);
}

#ifdef WIN32
namespace {
void InitWSA() {
  WSADATA wsa_data;

  if (WSAStartup(MAKEWORD(2, 2), &wsa_data)) { // initialize wsa
    PrintErrorMessageAndExit(CRUT("Failed to initialize wsa."));
  }
}
} // namespace

#endif

int CloseSocket(int socket) {
#ifdef WIN32
  return closesocket(socket);
#else
  return close(socket);
#endif
}

void BeforeExit() {
#ifdef WIN32
  WSACleanup();
#endif

  SignalAndWaitForOutputThreadStop();
}

String ReadInputLine() {
  String line;
  std::getline(input_stream, line);
  return line;
}

void SafeSend(int socket, std::string_view buffer) {
  const int total_byte_count = buffer.size();
  int byte_count_sent = 0;
  int retry_count = 0;

  while (true) {
    // Now we have sent all data.
    if (byte_count_sent == total_byte_count)
      break;

    auto byte_actually_sent = send(socket, buffer.data() + byte_count_sent,
                                   buffer.size() - byte_count_sent, 0);

    // send failed
    if (byte_actually_sent == -1) {
      SendOutput(OutputType::Error, CRUT("Failed to send!\n"));
      CloseSocket(socket);
      break;
    }

    byte_count_sent += byte_actually_sent;
  }
}

std::string SafeReadUntil(int socket, char c, std::string &rest) {
  std::string result = rest;

  const int buffer_size = 100;
  char *buffer = new char[buffer_size];

  while (true) {
    int received_number = recv(socket, buffer, buffer_size, 0);

    if (received_number == -1) {
      PrintErrorMessageAndExit(CRUT("Failed to recv."));
    }

    bool b = false;

    for (int i = 0; i < received_number; i++) {
      if (buffer[i] == c) {
        result.append(buffer, i);
        rest = std::string(buffer + i + 1, received_number - i - 1);
        b = true;
        break;
      }
    }

    if (b)
      break;

    result.append(buffer, received_number);
  }

  delete[] buffer;

  return result;
}

int main() {
#ifdef WIN32
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD mode;
  GetConsoleMode(h, &mode);
  mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(h, mode);

  InitWSA();
#endif

  int c = Main();

  BeforeExit();
  return c;
}
