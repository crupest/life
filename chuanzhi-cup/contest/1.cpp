#include <cstdio>

int main() {
  int n, v, m, a;
  std::scanf("%d%d%d%d", &n, &v, &m, &a);

  int money = 0;

  v -= a;

  for (int i = 0; i < n; i++) {
    if (i % m == 0) {
      v += a;
    }

    money += v;
  }

  std::printf("%d", money);

  return 0;
}