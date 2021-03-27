#include <algorithm>
#include <iostream>
#include <random>

const int kCommonDifference = 25;
const int kSequenceSize = 100;

int main() {

  std::random_device random_device;
  auto random = std::default_random_engine{random_device()};
  std::binomial_distribution<int> distribution{100, 0.4};

  std::vector<int> sequence;

  int current_value = 0;

  for (int i = 0; i < kSequenceSize; i++) {
    sequence.push_back(current_value);
    current_value += distribution(random) * kCommonDifference;
  }

  std::shuffle(sequence.begin(), sequence.end(), random);

  std::cout << kSequenceSize << "\n";
  for (auto v : sequence) {
    std::cout << v << ' ';
  }

  return 0;
}
