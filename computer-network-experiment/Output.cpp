#include "Output.h"

folly::MPMCQueue<Output> output_queue(100);

void OutputThread() {
  while (true) {
    Output output;
    output_queue.blockingRead(output);
    switch (output.type) {
    case OutputType::Error:
      error_stream << output.message;
      break;
    default:
      output_stream << output.message;
      break;
    }
  }
}
