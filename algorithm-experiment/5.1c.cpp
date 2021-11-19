#include <bitset>
#include <ios>
#include <iostream>

std::bitset<10000000> f;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long current;

  while (std::cin >> current) {
    f[current - 10000000].flip();
  }

  for (int i = 1; i < 10000000; ++i) {
    if (!f[i]) {
      std::cout << i + 10000000 << '\n';
    }
  }

  return 0;
}
