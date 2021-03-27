#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n;
  std::cin >> n;

  while (n) {
    std::cout << n << ' ';
    n /= 3;
  }

  return 0;
}
