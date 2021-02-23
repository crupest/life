#include <cmath>
#include <cstdio>

int main() {
  int x;
  std::scanf("%d", &x);

  double gpa;

  if (x >= 90)
    gpa = 4.0;
  else if (x >= 60) {
    gpa = (x - 50.0) / 10.0;
  } else {
    int s = std::floor(std::sqrt(x) * 10.0);
    if (s >= 90)
      gpa = 4.0;
    else if (s >= 60) {
      gpa = (s - 50.0) / 10.0;
    } else {
      gpa = 0;
    }
  }

  std::printf("%.1f", gpa);

  return 0;
}