#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> ns;

  while (!std::cin.eof() || std::cin) {
    int n;
    std::cin >> n;
    ns.push_back(n);
  }

  if (!std::cin.eof()) {
    std::cerr << "Failed to parse input.\n";
    return -1;
  }

  if (ns.size() % 2 != 0) {
    std::cerr << "Input integer number must be even.\n";
    return -1;
  }

  
}
