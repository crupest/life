#include <iostream>
#include <random>

using std::cout;

int main() {
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution<int> distribution(1, 100);
  const int SIZE = 100;
  cout << SIZE << '\n';
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      cout << (distribution(engine) < 75 ? '#' : '.');
    }
    cout << '\n';
  }
  return 0;
}
