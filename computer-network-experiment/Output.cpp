#include "Output.h"
#include "folly/CancellationToken.h"

folly::MPMCQueue<Output> output_queue(100);

folly::CancellationSource cancellation_source;

std::thread output_thread(OutputThread);

void PrintOutput(const Output &output) {
  switch (output.type) {
  case OutputType::Error:
    error_stream << output.message;
    break;
  default:
    output_stream << output.message;
    break;
  }
}

void OutputThread() {
  while (true) {
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
