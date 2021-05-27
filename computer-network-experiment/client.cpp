/** Created by crupest.
 *  This is the client program.
 */

#include <Windows.h>
#include <iostream>
#include <string>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")

const auto connect_address = "127.0.0.1"; // control connect address
const u_short port = 1234;                // control connect port

int main() {
  WSADATA wsa_data;

  if (WSAStartup(MAKEWORD(2, 2), &wsa_data)) // initialize wsa
  {
    std::cerr << "WSA start up error!\n";
    WSACleanup();
    return 1;
  }

  int client_socket;

  if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    std::cerr << "Failed to create socket!\n";
    WSACleanup();
    return 1;
  }

  sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = inet_addr(connect_address);
  memset(&(server_address.sin_zero), 0, sizeof(server_address.sin_zero));

  if (connect(client_socket, (sockaddr *)&server_address, sizeof(sockaddr)) ==
      SOCKET_ERROR) {
    std::cerr << "Failed to connect!";
    WSACleanup();
    return 1;
  }

  const int buffer_size = 100;
  char * buffer = new char[buffer_size];

  int received_number = recv(client_socket, buffer, buffer_size, 0);

  if (received_number == -1) {
    std::cerr <<  "Failed to recv.";
    WSACleanup();
    return 1;
  }

  std::string s(buffer, received_number);

  std::cout << "Received message:\n" << s; 

  closesocket(client_socket);
  WSACleanup();

  return 0;
}
