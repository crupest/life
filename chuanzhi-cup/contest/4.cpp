#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> files;
  int n;
  std::cin >> n;
  int current_count = 0;
  while (current_count < n) {
    std::string command;
    std::cin >> command;
    char a = command[0];
    if (a == 't') {
      std::string file;
      std::cin >> file;
      auto iter = std::find(files.cbegin(), files.cend(), file);
      if (iter == files.cend()) {
        files.push_back(std::move(file));
      }
    } else if (a == 'l') {
      for (const auto &f : files) {
        std::cout << f << '\n';
      }
    } else {
      char b = command[1];
      if (b == 'm') {
        std::string file;
        auto iter = std::find(files.cbegin(), files.cend(), file);
        if (iter != files.cend())
          files.erase(iter);
      } else {
        std::string old, new_f;
        std::cin >> old >> new_f;
        auto iter = std::find(files.begin(), files.end(), old);
        auto iter2 = std::find(files.begin(), files.end(), new_f);
        if (iter != files.end() && iter2 == files.end()) {
          *iter = std::move(new_f);
        }
      }
    }
    current_count++;
  }

  return 0;
}
