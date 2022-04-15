#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

void PrintMatrix(int n, double **a) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << a[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void PrintEquation(int n, double **a, double *b) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << a[i][j] << ' ';
    }
    std::cout << b[i] << '\n';
  }
}

void JacobianIteration(int n, double *x, double **a, double *b) {
  double *x_new = new double[n];

  for (int r = 0; r < n; r++) {
    x_new[r] = b[r];
    for (int c = 0; c < n; c++) {
      if (c != r) {
        x_new[r] -= a[r][c] * x[c];
      }
    }
    x_new[r] /= a[r][r];
  }

  for (int r = 0; r < n; r++) {
    x[r] = x_new[r];
  }

  delete[] x_new;
}

double GetDiff(int n, double *x, double **a, double *b) {
  double diff = 0;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      diff += a[r][c] * x[c];
    }
    diff -= b[r];
  }
  return diff;
}

int main() {
  std::cout << std::showpos << std::fixed << std::setprecision(3);

  const int n = 6;
  double **a = new double *[n];
  double *b = new double[n];
  double *x = new double[n];

  for (int i = 0; i < n; i++) {
    x[i] = 0;
    a[i] = new double[n];
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
    }
    std::cin >> b[i];
  }

  std::cout << "Equation:\n";
  PrintEquation(n, a, b);

  int count = 0;

  while (true) {
    std::cout << "Solution:\n";
    for (int i = 0; i < n; i++) {
      std::cout << x[i] << '\n';
    }

    double diff = GetDiff(n, x, a, b);
    std::cout << "diff: " << diff << '\n';
    if (std::abs(diff) < 1e-6)
      break;
    count++;
    std::cout << "Now doing iteration " << count << '\n';
    JacobianIteration(n, x, a, b);

    if (count > 100)
      break;
  }

  std::cout << "Final Solution:\n";
  for (int i = 0; i < n; i++) {
    std::cout << x[i] << '\n';
  }

  return 0;
}
