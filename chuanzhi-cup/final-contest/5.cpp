#include <algorithm>
#include <iostream>

int n, m;
int w[100010];
int c[100010];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;

  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }

  for (int i = 0; i < m; i++) {
    std::cin >> c[i];
  }

  std::sort(w, w + n);
  std::sort(c, c + m);

  int a = 0, b = 0;
  int count = 0;

  while (true) {
    if (a == n) {
      break;
    }
    if (b == m) {
      break;
    }

    if (w[a] >= c[b]) {
      a++;
      b++;
      count++;
    } else {
      a++;
    }
  }

  std::cout << count;

  return 0;
}
