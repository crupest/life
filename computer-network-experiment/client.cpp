/** Created by crupest.
 *  This is the client program.
 */

#include "Common.h"
#include "IO.h"

#include <folly/CancellationToken.h>
#include <folly/ProducerConsumerQueue.h>

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

namespace {
folly::ProducerConsumerQueue<std::string> send_queue(100);
folly::CancellationSource cancellation_source;
} // namespace

void PrintHelp() {
  SendOutput(CRUT("Input anything to send to server. Or just enter to receive "
                  "lastest messages from server.\n"));
}

void OnInputLine(StringView line) {
  if (line.empty()) {
    return;
  } else {
    send_queue.write(ConvertCharStringBack(line) + '\n');
  }
}

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

  output_stream << CRUT("Please input your name:\n> ");
  String name = ReadInputLine();

  PrintHelp();

  StartIOThread();

  name.push_back(CRUT('\n'));
  auto name_data = ConvertCharStringBack(name);
  SafeSend(client_socket, name_data);

  std::thread receive_thread([client_socket] {
    std::string rest;
    while (true) {
      if (cancellation_source.isCancellationRequested()) {
        break;
      }

      std::string s = SafeReadUntil(client_socket, '\n', rest);

      SendOutput(CRUT("Recived a message:\n{}\n"), ConvertCharString(s));
    }
  });
  receive_thread.detach();

  while (true) {
    if (cancellation_source.isCancellationRequested()) {
      break;
    }

    std::string s;
    if (send_queue.read(s)) {
      SafeSend(client_socket, s);
    }
  }

  CloseSocket(client_socket);
  return 0;
}
