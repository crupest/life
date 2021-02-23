#include <algorithm>
#include <iomanip>
#include <iostream>

int score[1000001];
double result[1000001];

int main() {
  int min;
  int max;
  int sum = 0;

  int count;
  std::cin >> count;

  for (int i = 1; i <= count; i++) {
    std::cin >> score[i];
  }

  int n1 = score[1], n2 = score[2];
  sum += n1 + n2;
  min = std::min(n1, n2);
  max = std::max(n1, n2);

  for (int i = 3; i <= count; i++) {
    int current = score[i];

    min = std::min(current, min);
    max = std::max(current, max);

    sum += current;

    int s = sum;
    s -= min;
    s -= max;

    result[i] = static_cast<double>(s) / (i - 2);
  }

  std::cout << std::fixed << std::setprecision(2);

  for (int i = 3; i <= count; i++) {
    std::cout << result[i] << "\n";
  }

  return 0;
}
