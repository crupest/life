#include "Output.h"

folly::MPMCQueue<Output> output_queue;

void OutputThread() {
  while (true) {
    Output output;
    output_queue.blockingRead(output);
    switch (output.type) {
    case OutputType::Error:
      std::wcerr << output.message;
      break;
    default:
      std::wcout << output.message;
      break;
    }
  }
}
