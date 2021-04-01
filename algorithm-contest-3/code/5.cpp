#include <algorithm>
#include <iostream>

int N, K;
long long A[100010];

long long M = 1000000009;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;

  for (int i = 0; i < N; i++) {
    std::cin >> A[i];
  }

  std::sort(A, A + N);

  long long result = 1;
  int left = 0, right = N - 1;
  long long sign = 1;
  int k = K;

  if (k % 2) {
    result = A[N - 1];
    right--;
    k--;

    if (result < 0) {
      sign = -1;
    }
  }

  while (k) {
    long long x = A[left] * A[left + 1], y = A[right] * A[right - 1];

    if (x * sign > y * sign) {
      result = x % M * result % M;
      left += 2;
    } else {
      result = y % M * result % M;
      right -= 2;
    }
    k -= 2;
  }

  std::cout << result;

  return 0;
}
