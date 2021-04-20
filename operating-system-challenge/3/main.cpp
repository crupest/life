#include <iostream>
#include <mutex>
#include <thread>

int main() {
  int turn = 1;
  int count = 0;
  std::mutex mutex;

  auto thread_proc1 = [&] {
    while (true) {
      {
        std::lock_guard<std::mutex> guard(mutex);
        if (count >= 10)
          break;
        if (turn == 1) {
          std::cout << "A" << std::endl;
          turn = 2;
        }
      }

      std::this_thread::yield();
    }
  };

  auto thread_proc2 = [&] {
    while (true) {
      {
        std::lock_guard<std::mutex> guard(mutex);
        if (count >= 10)
          break;
        if (turn == 2) {
          std::cout << "B" << std::endl;
          turn = 3;
        }
      }

      std::this_thread::yield();
    }
  };

  auto thread_proc3 = [&] {
    while (true) {
      {
        std::lock_guard<std::mutex> guard(mutex);
        if (count >= 10)
          break;
        if (turn == 3) {
          std::cout << "C" << std::endl;
          turn = 1;
          count++;
        }
      }

      std::this_thread::yield();
    }
  };

  std::thread thread1(thread_proc1);
  std::thread thread2(thread_proc2);
  std::thread thread3(thread_proc3);

  thread1.join();
  thread2.join();
  thread3.join();

  return 0;
}
