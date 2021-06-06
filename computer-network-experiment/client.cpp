/** Created by crupest.
 *  This is the client program.
 */

#include "Common.h"
#include "Output.h"

#ifdef WIN32
#include <Windows.h>
#include <winsock.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#endif

const auto connect_address = "127.0.0.1"; // control connect address
const u_short port = 1234;                // control connect port

int Main() {
  int client_socket;

  if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    PrintErrorMessageAndExit(CRUT("Failed to create socket!\n"));
  }

  sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = inet_addr(connect_address);
  memset(&(server_address.sin_zero), 0, sizeof(server_address.sin_zero));

  if (connect(client_socket, (sockaddr *)&server_address, sizeof(sockaddr)) ==
      -1) {
    PrintErrorMessageAndExit(CRUT("Failed to connect!"));
  }

  const int buffer_size = 100;
  char *buffer = new char[buffer_size];

  int received_number = recv(client_socket, buffer, buffer_size, 0);

  if (received_number == -1) {
    PrintErrorMessageAndExit(CRUT("Failed to recv."));
  }

  std::string s(buffer, received_number);

  SendOutput(CRUT("Received message:\n"));

  Close(client_socket);
  return 0;
}
