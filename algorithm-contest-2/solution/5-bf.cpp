#include <iostream>

int batteries[1000];

int main(void) {
  int N, K;
  std::cin >> N >> K;
  for (int i = 0; i < N; i++)
    std::cin >> batteries[i];

  int max = 0;
  int max_index[4];

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      for (int k = j + 1; k < N; k++) {
        for (int l = k + 1; l < N; l++) {
          int sum = batteries[i] + batteries[j] + batteries[k] + batteries[l];
          if (sum % K == 0 && sum > max) {
            max = sum;
            max_index[0] = i;
            max_index[1] = j;
            max_index[2] = k;
            max_index[3] = l;
          }
        }
      }
    }
  }

  std::cout << max;

  return 0;
}
