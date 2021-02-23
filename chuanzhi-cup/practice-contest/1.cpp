#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int count = 0;

  for (int i = 1; i <= n; i++) {
    int num = i;
    int sum = 0;
    while (num != 0) {
      sum += num % 10;
      num /= 10;

      if (sum > 9)
        break;
    }

    if (sum == 9)
      count++;
  }

  std::cout << count;

  return 0;
}
