#include "Semaphore.h"
#include "Thread.h"

#include <iostream>

int main() {
  unsigned data = 0;

  cru::Semaphore semaphore;

  cru::Thread t1([&data, &semaphore] {
    for (int i = 0; i < 100000; i++) {
      semaphore.P();
      data += 10;
      semaphore.V();
    }
  });

  cru::Thread t2([&data, &semaphore] {
    for (int i = 0; i < 100000; i++) {
      semaphore.P();
      data += 10;
      semaphore.V();
    }
  });

  std::cout << "Created thread: " << t1.GetNativeID() << '\n';
  std::cout << "Created thread: " << t2.GetNativeID() << '\n';

  t1.Join();
  t2.Join();
  std::cout << "Answer is " << data << ", which is "
            << (data == 2000000 ? "correct" : "false") << '\n';

  return 0;
}
