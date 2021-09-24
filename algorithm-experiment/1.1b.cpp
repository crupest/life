#include <iostream>

int main() {
  for (int i = 2; i <= 1000; i++) {
    std::cout << i << ',';

    int n = i;

    int k = 0;

    while (n != 1) {
      n = n % 2 ? n * 3 + 1 : n / 2;
      k++;
    }

    std::cout << k << '\n';
  }

  return 0;
}