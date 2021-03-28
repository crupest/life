#include <iostream>
#include <unordered_set>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::unordered_set<int> a;

  for (int i = 0; i < n; i++) {
    int j;
    std::cin >> j;
    a.insert(j);
  }

  int count = 0;

  for (int i = 0; i < m; i++) {
    int j;
    std::cin >> j;
    if (a.count(j)) {
      count++;
    }
  }

  std::cout << count;

  return 0;
}
