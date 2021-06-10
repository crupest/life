#include "Mutex.h"
#include "Thread.h"

#include <iostream>

int main() {

  unsigned data = 0;
  cru::Mutex mutex;
  mutex.Lock();

  cru::Thread t1([&data, &mutex] {
    for (int i = 0; i < 100000; i++) {
      mutex.Lock();
      data += 10;
      //std::cout << "Data is now: " << data << '\n';
      mutex.Unlock();
    }
  });

  cru::Thread t2([&data, &mutex] {
    for (int i = 0; i < 100000; i++) {
      mutex.Lock();
      data += 10;
      //std::cout << "Data is now: " << data << '\n';
      mutex.Unlock();
    }
  });

  std::cout << "Created thread: " << t1.GetNativeID() << '\n';
  std::cout << "Created thread: " << t2.GetNativeID() << '\n';

  mutex.Unlock();

  t1.Join();
  t2.Join();

  std::cout << "Answer is " << data << ", which is "
            << (data == 2000000 ? "correct" : "false") << '\n';

  return 0;
}
