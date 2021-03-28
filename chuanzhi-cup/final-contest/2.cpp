#include <iostream>

long long a[1010];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  long long count = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i] * a[j] <= k) {
        count++;
      }
    }
  }

  std::cout << count;

  return 0;
}
