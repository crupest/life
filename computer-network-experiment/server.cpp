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
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

const auto bind_address = "127.0.0.1"; // control bind address
const u_short port = 1234;             // control bind port

void ResponseThreadProc(int socket, sockaddr_in address) {
  auto address_string = inet_ntoa(address.sin_addr);

  std::string rest;

  std::string name = SafeReadUntil(socket, '\n', rest);

  SendOutput(CRUT("Connected to {}, whose name is {}."),
             ConvertCharString(address_string), ConvertCharString(name));

  CloseSocket(socket);
}

int Main() {
  int server_socket;

  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    PrintErrorMessageAndExit(CRUT("Failed to create socket."));
  }

  sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = inet_addr(bind_address);
  memset(&(server_address.sin_zero), 0, sizeof(server_address.sin_zero));

  if (bind(server_socket, reinterpret_cast<sockaddr *>(&server_address),
           sizeof(sockaddr_in)) == -1) {
    PrintErrorMessageAndExit(CRUT("Failed to bind."));
  }

  if (listen(server_socket, SOMAXCONN) == -1) {
    PrintErrorMessageAndExit(CRUT("Failed to listen."));
  }

  SendOutput(OutputColor::Green,
             CRUT("Now start to accept incoming connection.\n"));

  while (true) {
    sockaddr_in client_address;
    int client_socket;
    unsigned sin_size = sizeof(sockaddr_in);
    client_socket =
        accept(server_socket, reinterpret_cast<sockaddr *>(&client_address),
#ifdef WIN32
               reinterpret_cast<int *>
#endif
               (&sin_size));

    if (client_socket == -1) {
      PrintErrorMessageAndExit(CRUT("Failed to accecpt."));
    }

    std::thread response_thread(ResponseThreadProc, client_socket,
                                client_address);
    response_thread.detach();
  }
}
