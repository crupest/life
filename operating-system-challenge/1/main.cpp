// Remember not to use O2 optimization!

#include <thread>
#include <vector>

int main() {
  std::vector<std::thread> threads;

  // Because my CPU has 4-core and 8-threads. I open 8 threads.
  for (int i = 0; i < 8; i++) {
    std::thread t([] {
      int i;
      int j;
      int k;
      double d;
      while (true) {
        i = i + i;
        j = j - j;
        k = k * k;
        d = d + d;
        i = i & i;
        j = j | j;
      }
    });
    threads.push_back(std::move(t));
  }

  for (auto &t : threads) {
    t.join();
  }

  return 0;
}
