#include "Thread.h"

#include <iostream>
#include <string>

int main() {
  cru::Thread thread1([](const std::string &s) { std::cout << s; },
                      "Hello world! 1\n");
  thread1.Join();

  cru::Thread thread2([](const std::string &s) { std::cout << s; },
                      "Hello world! 2\n");
  thread2.Join();

  return 0;
}
