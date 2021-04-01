#include <iostream>

int n, m;
long long f[31][31];

int main() {
  std::cin >> n >> m;

  f[1][1] = 1;

  for (int r = 1; r <= n; r++) {
    for (int c = 1; c <= m; c++) {
      if (!(r == 1 && c == 1) && !(r % 2 == 0 && c % 2 == 0)) {
        f[r][c] = f[r - 1][c] + f[r][c - 1];
      }
    }
  }

  std::cout << f[n][m];

  return 0;
}
