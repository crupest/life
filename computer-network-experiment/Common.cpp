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
void InitWSA() {
  WSADATA wsa_data;

  if (WSAStartup(MAKEWORD(2, 2), &wsa_data)) { // initialize wsa
    PrintErrorMessageAndExit(CRUT("Failed to initialize wsa."));
  }
}
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
