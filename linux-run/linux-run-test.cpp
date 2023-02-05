#include "linux-run.h"

#include <iostream>
#include <stdexcept>

int main() {
  using namespace linux_run;
  RunOptions options;
  options.timeout_in_second = 1;

  bool caught_timeout_error = false;

  try {
    run("./linux-run-test-bin", {}, options);
  } catch (const TimeoutError &e) {
    caught_timeout_error = true;
  }

  if (!caught_timeout_error) {
    throw std::runtime_error("Test failed. TimeoutError was not thrown.");
  } else {
    std::cout << "Test succeeded. TimeoutError caught.\n";
  }

  return 0;
}
