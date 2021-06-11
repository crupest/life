#include "Thread.h"

#include <iostream>

const long long N = 1e9;

int main(int argc, char **argv) {
  int thread_number;
  if (argc == 1) {
    thread_number = 1;
  } else if (argc == 2) {
    thread_number = std::atoi(argv[1]);
    if (thread_number <= 0) {
      std::cerr << "Argument must be a positive integer.\n";
    }
  } else {
    std::cerr << "Too many arguments.\n";
  }

  std::cout << "Use " << thread_number << " threads to calculate sum of 1-" << N
            << ".\n";

  if (thread_number == 1) {
    long long sum = 0;
    for (long long i = 1; i <= 1e9; i++) {
      sum += i;
    }
    std::cout << "Sum of 1-" << N << " is " << sum << '\n';
  } else {
    std::vector<cru::Thread> threads(thread_number);
    std::vector<long long> partial_sum(thread_number);

    long long step = N / thread_number;

    for (int i = 0; i < thread_number; i++) {
      long long start = step * i;
      long long end = step * (i + 1);

      long long &ps = partial_sum[i];

      if (i == thread_number - 1) {
        threads[i] = cru::Thread([&ps, start] {
          long long sum = 0;
          for (long long j = start; j <= 1e9; j++) {
            sum += j;
          }
          ps = sum;
        });
      } else {
        threads[i] = cru::Thread([&ps, start, end] {
          long long sum = 0;
          for (int j = start; j < end; j++) {
            sum += j;
          }
          ps = sum;
        });
      }
    }

    for (auto &thread : threads) {
      thread.Join();
    }

    long long sum = 0;
    for (auto ps : partial_sum) {
      sum += ps;
    }

    std::cout << "Sum of 1-" << N << " is " << sum << '\n';
  }

  return 0;
}
