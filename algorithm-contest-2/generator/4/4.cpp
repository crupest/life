#include <iostream>
#include <random>
#include <vector>

using std::cout;

int main() {
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution<int> distribution(1, 1000);
  const int SIZE = 100;
  std::vector<int> b;

  for (int i = 0; i < SIZE * 2; i++) {
    b.push_back(distribution(engine));
  }

  long long sum = 0;
  for (int i = 0; i < SIZE; i++) {
    sum += b[i * 2] * b[i * 2 + 1];
  }

  cout << SIZE << ' ' << (sum + 10) << '\n';

  for (int i = 0; i < SIZE; i++) {
    cout << b[i * 2] << ' ' << b[i * 2 + 1] << '\n';
  }

  return 0;
}
