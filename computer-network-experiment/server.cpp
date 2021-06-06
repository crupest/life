/** Created by crupest.
 *  This is the server program.
 */

#include "Output.h"

#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <thread>

#include <Windows.h>
#include <winsock.h>

#pragma comment(lib, "Ws2_32.lib")

const auto bind_address = "127.0.0.1"; // control bind address
const u_short port = 1234;             // control bind port


[[noreturn]] void
PrintErrorMessageAndExit(std::wstring_view message,
                         std::optional<int> error_code = std::nullopt) {

  SendOutput(L"{}\n", message);

  if (error_code) {
    SendOutput(OutputType::Error, L"Error code is {}.\n", *error_code);
    wchar_t buffer[500];
    if (!FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
                            FORMAT_MESSAGE_ARGUMENT_ARRAY |
                            FORMAT_MESSAGE_IGNORE_INSERTS,
                        nullptr, *error_code, 0, buffer, 500, nullptr)) {
      SendOutput(OutputType::Error, L"Failed to format error message.\n");
    } else {
      SendOutput(OutputType::Error, L"{}\n", buffer);
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
