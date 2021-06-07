/** Created by crupest.
 *  This is the server program.
 */

#include "Common.h"
#include "IO.h"

#include <folly/CancellationToken.h>
#include <folly/ProducerConsumerQueue.h>

#include <optional>
#include <stdint.h>
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

void PrintHelp() {
  SendOutput(CRUT(
      "Input and run one of following command:\n\t> NOTHING -> Continue and "
      "print new messages.\n\t> list -> List all connected client.\n\t> send "
      "[i] [message] -> Send messages to client with number i.\n"));
}

struct Connection {
  int id;
  std::thread thread;
  int socket;
  sockaddr_in address;
  String address_string;
  String name;
  folly::ProducerConsumerQueue<std::string> send_queue{100};
  folly::CancellationSource cancellation_source;
};

std::vector<Connection> connections;

void ResponseThreadProc(Connection *connection) {
  auto host = ConvertCharString(inet_ntoa(connection->address.sin_addr));
  auto port = htons(connection->address.sin_port);
  connection->address_string = fmt::format(CRUT("{}:{}"), host, port);

  std::string rest;

  std::string n = SafeReadUntil(connection->socket, '\n', rest);
  connection->name = ConvertCharString(n);
  SendOutput(CRUT("Connected to {}, whose name is {}."),
             connection->address_string, connection->name);

  std::thread revieve_thread(
      [](Connection *connection) {
        std::string rest;
        while (true) {
          if (connection->cancellation_source.isCancellationRequested()) {
            break;
          }

          std::string s = SafeReadUntil(connection->socket, '\n', rest);

          SendOutput(CRUT("{}({}) send a message:\n{}\n"), connection->name,
                     connection->address_string, ConvertCharString(s));
        }
      },
      connection);

  while (true) {
    if (connection->cancellation_source.isCancellationRequested()) {
      break;
    }

    std::string s;
    if (connection->send_queue.read(s)) {
      SafeSend(connection->socket, s);
    }
  }

  CloseSocket(connection->socket);
}

void OnInputLine(StringView line) { StringStream ss{String(line)};
  ss.
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

  StartIOThread();

  int current_id = 1;

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

    Connection connection;
    connection.id = current_id++;
    connection.socket = client_socket;
    connection.address = client_address;
    connections.push_back(std::move(connection));

    connection.thread = std::thread(ResponseThreadProc, &connections.back());
    connection.thread.detach();
  }
}
