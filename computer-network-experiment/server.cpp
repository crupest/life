/** Created by crupest.
 *  This is the server program.
 */

#include "Common.h"
#include "Output.h"

#include <optional>
#include <thread>

#ifdef WIN32
#include <Windows.h>
#include <winsock.h>
#endif

const auto bind_address = "127.0.0.1"; // control bind address
const u_short port = 1234;             // control bind port

void ResponseThreadProc(int socket, sockaddr_in address) {
  auto address_string = inet_ntoa(address.sin_addr);
  SendOutput(CRUT("Connected to {}!\n"), ConvertCharString(address_string));

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

  SendOutput(CRUT("Succeeded to send message to {} !\n"),
             ConvertCharString(address_string));

  closesocket(socket);
}

int Main() {
  int server_socket;

  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    PrintErrorMessageAndExit(CRUT("Failed to create socket."));
  }

  sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = inet_addr(bind_address);
  memset(&(server_address.sin_zero), 0, sizeof(server_address.sin_zero));

  if (bind(server_socket, reinterpret_cast<sockaddr *>(&server_address),
           sizeof(sockaddr_in)) == SOCKET_ERROR) {
    PrintErrorMessageAndExit(CRUT("Failed to bind."));
  }

  if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
    PrintErrorMessageAndExit(CRUT("Failed to listen."));
  }

  while (true) {
    sockaddr_in client_address;
    int client_socket;
    int sin_size = sizeof(sockaddr_in);
    client_socket =
        accept(server_socket, reinterpret_cast<sockaddr *>(&client_address),
               &sin_size);

    if (client_socket == INVALID_SOCKET) {
      PrintErrorMessageAndExit(CRUT("Failed to accecpt"));
    }

    std::thread response_thread(ResponseThreadProc, client_socket,
                                client_address);
    response_thread.detach();
  }
}
