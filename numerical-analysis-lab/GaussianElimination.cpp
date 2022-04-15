#include <cstdlib>
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

bool HasSolution(int n, double **a, double *b) {
  for (int r = 0; r < n; r++) {
    bool all_zero = true;
    for (int c = 0; c < n; c++) {
      if (a[r][c] != 0) {
        all_zero = false;
        break;
      }
    }

    if (all_zero && b[r] != 0) {
      return false;
    }
  }
  return true;
}

void GaussianElimination(int n, double **a, double *b) {
  for (int c = 0; c < n; c++) {
    int pivot_r = -1;
    for (int r = c; r < n; r++) {
      if (a[r][c] != 0) {
        pivot_r = r;
        break;
      }
    }

    if (pivot_r == -1) {
      continue;
    }

    double pivot = a[pivot_r][c];

    for (int r = 0; r < n; r++) {
      if (r == pivot_r) {
        continue;
      }

      double factor = a[r][c] / pivot;

      for (int i = 0; i < n; i++) {
        a[r][i] -= factor * a[pivot_r][i];
        b[i] -= factor * b[pivot_r];
      }
    }

    for (int i = 0; i < n; i++) {
      a[pivot_r][i] /= pivot;
      b[pivot_r] /= pivot;
    }
  }
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

  for (int i = 0; i < n; i++) {
    a[i] = new double[n];
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
    }
    std::cin >> b[i];
  }

  std::cout << "Equation:\n";
  PrintEquation(n, a, b);

  GaussianElimination(n, a, b);
  std::cout << "After Gaussian Elimination:\n";
  PrintEquation(n, a, b);

  if (!HasSolution(n, a, b)) {
    std::cout << "No solution!\n";
  }

  if (std::abs(GetDiff(n, b, a, b)) > 1e-6) {
    std::cout << "Solution examination failed!\n";
  } else {
    std::cout << "Solution examination passed!\n";
  }

  return 0;
}
