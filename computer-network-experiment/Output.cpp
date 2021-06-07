#include "Output.h"

#include <folly/CancellationToken.h>

#include <mutex>
#include <ostream>
#include <type_traits>

std::mutex m;

folly::MPMCQueue<Output> output_queue(100);

folly::CancellationSource cancellation_source;

std::thread output_thread(OutputThread);

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

void OutputThread() {
  while (true) {
    std::lock_guard<std::mutex> guard(m);

    if (cancellation_source.getToken().isCancellationRequested()) {
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
    if (output_queue.readIfNotEmpty(output))
      PrintOutput(output);
  }
}

void SignalAndWaitForOutputThreadStop() {
  cancellation_source.requestCancellation();
  output_thread.join();
}

std::lock_guard<std::mutex> BlockOutputThread() {
  return std::lock_guard<std::mutex>(m);
}
