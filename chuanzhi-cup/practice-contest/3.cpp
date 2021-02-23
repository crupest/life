#include <cmath>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

int main() {
  std::string input;
  std::getline(std::cin, input);

  std::regex reg(R"aaa((\d+)([GMK]?B)=\?([GMK]?B))aaa");
  std::smatch match;
  std::regex_match(input, match, reg);

  std::string original_number_str = match[1].str();
  std::string original_unit = match[2].str();
  std::string target_unit = match[3].str();

  double original_number = std::stod(original_number_str);

  auto to_ratio = [](const std::string s) -> double {
    if (s.size() == 1)
      return 1;
    if (s[0] == 'G')
      return std::pow(2, 30);
    if (s[0] == 'M')
      return std::pow(2, 20);
    return std::pow(2, 10);
  };

  double original_ratio = to_ratio(original_unit);
  double target_ratio = to_ratio(target_unit);

  std::cout << std::fixed << std::setprecision(6)
            << (original_number * original_ratio / target_ratio);

  return 0;
}
