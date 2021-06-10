#include "Thread.h"

#include <iostream>

int main() {
  unsigned data = 0;

  cru::Thread t1([&data] {
    for (int i = 0; i < 100000; i++)
      data += 10;
  });

  cru::Thread t2([&data] {
    for (int i = 0; i < 100000; i++)
      data += 10;
  });

  std::cout << "Created thread: " << t1.GetNativeID() << '\n';
  std::cout << "Created thread: " << t2.GetNativeID() << '\n';

  t1.Join();
  t2.Join();
  std::cout << "Answer is " << data << ", which is "
            << (data == 200000 ? "correct" : "false") << '\n';

  return 0;
}
