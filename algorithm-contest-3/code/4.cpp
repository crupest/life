#include <algorithm>
#include <iostream>
#include <numeric>

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int N;
int A[100010];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 0; i < N; i++) {
    std::cin >> A[i];
  }

  std::sort(A, A + N);

  int g = A[1] - A[0];
  for (int i = 1; i < N - 1; i++) {
    g = gcd(g, A[i + 1] - A[i]);
  }

  if (g == 0) {
    std::cout << N;
  } else {
    std::cout << (A[N - 1] - A[0]) / g + 1;
  }

  return 0;
}
