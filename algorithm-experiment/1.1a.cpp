#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int k = 0;

  while (n != 1) {
    n = n % 2 ? n * 3 + 1 : n / 2;
    k++;
  }

  std::cout << k << std::endl;

  return 0;
}