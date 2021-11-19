#include <bitset>
#include <ios>
#include <iostream>

std::bitset<10000000> f;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (true) {
    long long current;
    std::cin >> current;

    auto b = f[current - 10000000];
    if (b) {
      std::cout << current;
      break;
    } else {
      b = true;
    }
  }

  return 0;
}
