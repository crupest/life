#include <cctype>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;

  for (int i = 0; i < T; i++) {
    int _a, _b;
    std::cin >> _a >> _b;
    std::string a, b;
    std::cin >> a >> b;

    for (char &c : a) {
      c = std::tolower(c);
    }

    for (char &c : b) {
      c = std::tolower(c);
    }

    int count = 0;

    for (int i = 0; i < b.size() - a.size() + 1; i++) {
      if (a == b.substr(i, a.size())) {
        count++;
      }
    }

    std::cout << count << "\n";
  }

  return 0;
}
