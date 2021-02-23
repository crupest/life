#include <cstdio>
#include <set>

struct V {
  V(int n, int t, int k) : n(n), t(t), k(k), c(t * k) {}

  int n;
  int t;
  int k;
  const int c;
};

struct C {
  bool operator()(const V &left, const V &right) const {
    if (left.c > right.c)
      return true;
    else if (left.c < right.c)
      return false;
    else if (left.t > right.t)
      return true;
    else if (left.t < right.t)
      return false;
    else if (left.n < right.n)
      return true;
    return false;
  }
};

int main() {
  std::set<V, C> data;

  int n;
  std::scanf("%d", &n);

  for (int i = 1; i <= n; i++) {
    int t, k;
    std::scanf("%d%d", &t, &k);
    data.insert(V{i, t, k});
  }

  for (const auto &v : data) {
    std::printf("%d ", v.n);
  }

  return 0;
}