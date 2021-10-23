#include <dlib/optimization/max_cost_assignment.h>
#include <iostream>
#include <vector>

#include <dlib/optimization.h>

int main() {
  int n;
  std::cin >> n;

  dlib::matrix<int> matrix(n, n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int l;
      std::cin >> l;
      matrix(i, j) = -l;
    }
  }

  auto result = dlib::max_cost_assignment(matrix);

  for (auto i : result) {
    std::cout << i << ' ';
  }

  std::cout << '\n';

  int sum = 0;

  for (int i = 0; i < n; i++) {
    sum += matrix(i, result[i]);
  }

  std::cout << sum;

  return 0;
}
