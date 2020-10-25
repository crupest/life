#include <iostream>
#include <random>
#include <vector>

using std::cout;

int main() {
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution<int> insert_distribution(0, 997);
  std::uniform_int_distribution<int> distribution(1, 100000);
  const int SIZE = 1000;
  std::vector<int> v;

  for (int i = 0; i < SIZE - 1; i++) {
    v.push_back(distribution(engine));
  }

  int K = 320;

  int a_index = insert_distribution(engine);
  int a = v[a_index];
  int b_index = insert_distribution(engine);
  while (b_index == a_index) {
    b_index = insert_distribution(engine);
  }
  int b = v[b_index];

  int c_index = insert_distribution(engine);
  while (c_index == a_index && c_index == b_index) {
    c_index = insert_distribution(engine);
  }
  int c = v[c_index];

  int d = (((-a - b - c) % K + K) % K) + 20 * K;

  int d_index = insert_distribution(engine);

  v.insert(v.cbegin() + d_index, c);

  cout << SIZE << ' ' << K << '\n';

  for (int i = 0; i < SIZE; i++) {
    cout << v[i] << ' ';
  }

  return 0;
}
