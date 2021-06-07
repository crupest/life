#include "IO.h"

#include <folly/CancellationToken.h>

#include <mutex>
#include <ostream>
#include <thread>
#include <type_traits>

folly::MPMCQueue<Output> output_queue(100);

folly::CancellationSource cancellation_source;

std::thread io_thread;

void PrintOutput(const Output &output) {
  std::basic_ostream<Char> *stream;

  switch (output.type) {
  case OutputType::Error:
    stream = &error_stream;
    break;
  default:
    stream = &output_stream;
    break;
  }

  switch (output.color) {
  case OutputColor::Normal:
    (*stream) << output.message;
    break;
  case OutputColor::Green:
    (*stream) << CRUT("\x1b[32m") << output.message << CRUT("\x1b[39m")
              << std::flush;
    break;
  case OutputColor::Red:
    (*stream) << CRUT("\x1b[31m") << output.message << CRUT("\x1b[39m")
              << std::flush;
    break;
  case OutputColor::Yellow:
    (*stream) << CRUT("\x1b[33m") << output.message << CRUT("\x1b[39m")
              << std::flush;
    break;
  }
}

String ReadInputLine() {
  String line;
  std::getline(input_stream, line);
  return line;
}

void IOThread() {
  while (true) {
    if (cancellation_source.isCancellationRequested()) {
      while (true) {
        Output output;
        if (output_queue.readIfNotEmpty(output)) {
          PrintOutput(output);
        } else {
          return;
        }
      }
    }

    Output output;
    while (output_queue.readIfNotEmpty(output))
      PrintOutput(output);

    PrintOutput({CRUT("> ")});
    OnInputLine(ReadInputLine());
  }
}

void SignalAndWaitForOutputThreadStop() {
  cancellation_source.requestCancellation();
  io_thread.join();
}

void StartIOThread() { io_thread = std::thread(IOThread); }
