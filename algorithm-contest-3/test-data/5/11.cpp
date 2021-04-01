#include <algorithm>
#include <iostream>
#include <random>

const int kNumberCount = 1000;
const int kChooseCount = 200;

int main() {
  std::random_device random_device;
  auto random = std::default_random_engine{random_device()};
  std::uniform_int_distribution<int> distribution{0, 200000};

  std::cout << kNumberCount << ' ' << kChooseCount << "\n";

  for (int i = 0; i < kNumberCount; i++) {
    std::cout << distribution(random) - 100000 << "\n";
  }

  return 0;
}
