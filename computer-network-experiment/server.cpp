/** Created by crupest.
 *  This is the server program.
 */

#include "Common.h"
#include "IO.h"
#include "ReadWriteLock.h"

#include <folly/CancellationToken.h>
#include <folly/ProducerConsumerQueue.h>

#include <algorithm>
#include <memory>
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

namespace {
void PrintHelp() {
  SendOutput(CRUT(
      "Input and run one of following command:\n\t> NOTHING -> Continue and "
      "print new messages.\n\t> list -> List all connected client.\n\t> send "
      "[i] [message] -> Send messages to client with number i.\n"));
}
} // namespace

struct Connection {
  int id;
  std::thread thread;
  std::thread receive_thread;
  int socket;
  sockaddr_in address;
  String address_string;
  String name;
  folly::ProducerConsumerQueue<std::string> send_queue{100};
  folly::CancellationSource cancellation_source;
};

namespace {
cru::ReadWriteLock connections_lock;
std::vector<std::unique_ptr<Connection>> connections;

void RemoveConnection(int id) {
  connections_lock.WriteLock();
  connections.erase(
      std::remove_if(connections.begin(), connections.end(),
                     [id](const std::unique_ptr<Connection> &connection) {
                       return connection->id == id;
                     }),
      connections.end());

  connections_lock.WriteUnlock();
}

void PrintConnections() {
  connections_lock.ReadLock();
  if (connections.empty()) {
    SendOutput(CRUT("Currently there is no connection.\n"));
  }

  String s;
  for (const auto &connection : connections) {
    s += fmt::format(CRUT("{}: {}({})\n"), connection->id, connection->name,
                     connection->address_string);
  }
  SendOutput(s);
  connections_lock.ReadUnlock();
}
} // namespace

void ResponseThreadProc(Connection *connection) {
  auto host = ConvertCharString(inet_ntoa(connection->address.sin_addr));
  auto port = htons(connection->address.sin_port);
  connection->address_string = fmt::format(CRUT("{}:{}"), host, port);

  std::string rest;
  std::string name_data;
  if (!SafeReadUntil(connection->socket, '\n', name_data, rest)) {
    SendOutput(OutputType::Error, CRUT("Failed to read name of {}.\n"),
               connection->address_string);
    CloseSocket(connection->socket);
    return;
  }

  connection->name = ConvertCharString(name_data);
  SendOutput(OutputColor::Green, CRUT("Connected to {}, whose name is {}.\n"),
             connection->address_string, connection->name);

  connection->receive_thread = std::thread(
      [](Connection *connection) {
        std::string rest;
        while (true) {
          if (connection->cancellation_source.isCancellationRequested()) {
            break;
          }

          std::string data;

          if (!SafeReadUntil(connection->socket, '\n', data, rest)) {
            SendOutput(OutputType::Error,
                       CRUT("Failed read data from socket of {}({}).\n"),
                       connection->name, connection->address_string);
            connection->cancellation_source.requestCancellation();
            return;
          }

          SendOutput(CRUT("{}({}) send a message:\n{}\n"), connection->name,
                     connection->address_string, ConvertCharString(data));
        }
      },
      connection);
  connection->receive_thread.detach();

  while (true) {
    if (connection->cancellation_source.isCancellationRequested()) {
      break;
    }

    std::string s;
    if (connection->send_queue.read(s)) {
      if (!SafeSend(connection->socket, s)) {
        SendOutput(OutputType::Error, CRUT("Failed send data to {}({}).\n"),
                   connection->name, connection->address_string);
        connection->cancellation_source.requestCancellation();
        break;
      }
    }
  }

  CloseSocket(connection->socket);

  RemoveConnection(connection->id);
}

void OnInputLine(StringView line) {
  StringStream ss{String(line)};

  ss >> std::ws;
  if (ss.eof())
    return;

  String command;
  ss >> command;

  if (command == CRUT("list")) {
    if (!ss.eof()) {
      SendOutput(OutputType::Error,
                 CRUT("List command can't have arguments!\n"));
      PrintHelp();
    } else {
      PrintConnections();
    }
    return;
  } else if (command == CRUT("send")) {
    int id;
    ss >> id;
    if (!ss) {
      SendOutput(OutputType::Error, CRUT("Send format error!\n"));
      PrintHelp();
      return;
    }

    String message;
    getline(ss, message);

    if (message.empty()) {
      SendOutput(OutputType::Error, CRUT("Send message can't be empty.!\n"));
      PrintHelp();
      return;
    }

    auto i = std::find_if(
        connections.begin(), connections.end(),
        [id](const std::unique_ptr<Connection> &c) { return c->id == id; });

    if (i == connections.end()) {
      SendOutput(OutputType::Error, CRUT("No connection with such id.\n"));
      return;
    }

    (*i)->send_queue.write(ConvertCharStringBack(message) + "\n");
    return;
  } else {
    SendOutput(OutputType::Error, CRUT("Unkown command!\n"));
    PrintHelp();
    return;
  }
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

  PrintHelp();

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

    connections_lock.WriteLock();
    connections.push_back(std::make_unique<Connection>());
    const std::unique_ptr<Connection> &connection = connections.back();

    connection->id = current_id++;
    connection->socket = client_socket;
    connection->address = client_address;
    connection->thread =
        std::thread(ResponseThreadProc, connections.back().get());
    connection->thread.detach();
    connections_lock.WriteUnlock();
  }
}
