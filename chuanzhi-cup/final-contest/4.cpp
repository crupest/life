#include <iostream>
#include <map>

std::map<int, int> c[3];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;

  std::cin >> n >> m;

  for (int i = 0; i < 3; i++) {
    auto &cc = c[i];
    for (int j = 0; j < n; j++) {
      int k;
      std::cin >> k;
      cc[k]++;
    }
  }

  int current = 0;
  std::pair<int, int> last;
  int last_put = 0;

  while (true) {
    auto &cc = c[current];

    if (current == last_put) {
      auto i = cc.begin();
      last.first = i->first;
      last.second = 1;
      if (i->second == 1) {
        cc.erase(i);
      } else {
        i->second--;
      }
      last_put = current;
    } else {
      bool can = false;

      for (auto i = cc.upper_bound(last.first); i != cc.end(); ++i) {
        if (i->second >= last.second) {
          can = true;
          i->second -= last.second;
          last.first = i->first;
          if (i->second == 0) {
            cc.erase(i);
          }
          break;
        }
      }

      if (!can) {
        auto end = cc.upper_bound(last.first);
        for (auto i = cc.begin(); i != end; ++i) {
          if (i->second > last.second) {
            can = true;
            i->second -= last.second + 1;
            last.first = i->first;
            last.second++;
            if (i->second == 0) {
              cc.erase(i);
            }
            break;
          }
        }
      }

      if (can) {
        last_put = current;
      }
    }

    if (cc.empty()) {
      std::cout << current + 1;
      break;
    }

    current++;
    current %= 3;
  }

  return 0;
}
