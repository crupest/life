#include <iostream>

long long sqrt(long long num) {
  long long left = 1, right = num;
  while (left != right) {
    long long mid = (left + right) / 2;
    if (mid * mid < num) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}

int main() {
  long long c;
  std::cin >> c;

  for (long long i = 1; i < c; i++) {
    long long b2 = c * c - i * i;
    long long b = sqrt(b2);
    if (b * b == b2) {
      std::cout << i << " " << b;
      break;
    }
  }

  return 0;
}
