/** Created by crupest.
 *  This is the server program.
 */

#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <thread>

#include <fmt/format.h>
#include <folly/MPMCPipeline.h>
#include <folly/MPMCQueue.h>

#include <Windows.h>
#include <winsock.h>

#include "StringUtil.hpp"
#include "fmt/core.h"

#pragma comment(lib, "Ws2_32.lib")

const auto bind_address = "127.0.0.1"; // control bind address
const u_short port = 1234;             // control bind port

enum class OutputType { Normal, Error };

struct Output {
  Output() = default;
  Output(std::wstring message, OutputType type = OutputType::Normal)
      : message(std::move(message)), type(type) {}

  CRU_DEFAULT_COPY(Output)
  CRU_DEFAULT_MOVE(Output)
  ~Output() = default;

  std::wstring message;
  OutputType type;
};

folly::MPMCQueue<Output> output_queue;

void SendOutput(std::wstring output) {
  output_queue.blockingWrite(std::move(output));
}

void SendOutput(Output output) {
  output_queue.blockingWrite(std::move(output));
}

template <typename... Args>
void SendOutput(std::wstring_view format, Args &&...args) {
  output_queue.blockingWrite(fmt::format(format, std::forward<Args>(args)...));
}

template <typename... Args>
void SendOutput(OutputType type, std::wstring_view format, Args &&...args) {
  output_queue.blockingWrite(
      {fmt::format(format, std::forward<Args>(args)...), type});
}

void OutputThread() {
  while (true) {
    Output output;
    output_queue.blockingRead(output);
    switch (output.type) {
    case OutputType::Error:
      std::wcerr << output.message;
      break;
    default:
      std::wcout << output.message;
      break;
    }
  }
}

[[noreturn]] void
PrintErrorMessageAndExit(std::wstring_view message,
                         std::optional<int> error_code = std::nullopt) {

  SendOutput(L"{}\n", message);

  if (error_code) {
    std::cerr << L"Error code is " << std::hex << *error_code << L'\n';
    wchar_t buffer[500];
    if (!FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
                            FORMAT_MESSAGE_ARGUMENT_ARRAY |
                            FORMAT_MESSAGE_IGNORE_INSERTS,
                        nullptr, *error_code, 0, buffer, 500, nullptr)) {
      std::wcerr << L"Failed to format error message.\n";
    } else {
      std::wcerr << buffer << L'\n';
    }
  }

  WSACleanup();

  std::exit(1);
}

void ResponseThreadProc(int socket, sockaddr_in address) {
  auto address_string = inet_ntoa(address.sin_addr);
  SendOutput(L"Connected to {}!\n", cru::ToUtf16WString(address_string));

  const std::string_view buffer = "Love you!!! By crupest!";

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
    if (byte_actually_sent == SOCKET_ERROR) {
      std::cerr << "Failed to send!\n";
      closesocket(socket);
      break;
    }

    byte_count_sent += byte_actually_sent;
  }

  SendOutput(L"Succeeded to send message to {} !\n",
             cru::ToUtf16WString(address_string));

  closesocket(socket);
}

int main() {
  WSADATA wsa_data;

  if (WSAStartup(MAKEWORD(2, 2), &wsa_data)) { // initialize wsa
    PrintErrorMessageAndExit(L"Failed to initialize wsa.", WSAGetLastError());
  }

  int server_socket;

  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    PrintErrorMessageAndExit(L"Failed to create socket.", WSAGetLastError());
  }

  sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = inet_addr(bind_address);
  memset(&(server_address.sin_zero), 0, sizeof(server_address.sin_zero));

  if (bind(server_socket, reinterpret_cast<sockaddr *>(&server_address),
           sizeof(sockaddr_in)) == SOCKET_ERROR) {
    PrintErrorMessageAndExit(L"Failed to bind.", WSAGetLastError());
  }

  if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
    PrintErrorMessageAndExit(L"Failed to listen.", WSAGetLastError());
  }

  while (true) {
    sockaddr_in client_address;
    int client_socket;
    int sin_size = sizeof(sockaddr_in);
    client_socket =
        accept(server_socket, reinterpret_cast<sockaddr *>(&client_address),
               &sin_size);

    if (client_socket == INVALID_SOCKET) {
      PrintErrorMessageAndExit(L"Failed to accecpt", WSAGetLastError());
    }

    std::thread response_thread(ResponseThreadProc, client_socket,
                                client_address);
    response_thread.detach();
  }
}
