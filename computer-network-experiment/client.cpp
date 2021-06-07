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

  String name;
  {
    auto guard = BlockOutputThread();
    output_stream << CRUT("Please input your name:");
    name = ReadInputLine();
  }

  name.push_back(CRUT('\n'));
  auto name_data = ConvertCharStringBack(name);
  SafeSend(client_socket, name_data);

  CloseSocket(client_socket);
  return 0;
}
