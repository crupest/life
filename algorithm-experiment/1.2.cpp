#include <algorithm>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>

const int MAXN = 2000000000;
long long pri[100000000];
std::bitset<MAXN> vis;
int cnt = 0;

void init() {
  for (int i = 2; i < MAXN; ++i) {
    if (!vis[i]) {
      pri[cnt++] = i;
      vis[i] = true;
    } // vis[i]置为true或不置true都可以
    for (int j = 0; j < cnt; ++j) {
      if (i * pri[j] >= MAXN) //判断是否越界
        break;
      vis[i * pri[j]] = true; //筛数
      if (i % pri[j] == 0)    //时间复杂度为O(n)的关键！
        break;
    }
  }
}

int main() {
  init();

  while (!std::cin.eof()) {
    long long n;
    std::cin >> n;

    bool b = false;

    if (n == 1 || n == 0) {
      continue;
    }

    if (std::binary_search(pri, pri + cnt, n)) {
      std::cout << n << '\n';
      continue;
    }

    for (int i = 0; i < cnt; i++) {
      if (n % pri[i] == 0) {
        b = true;
        break;
      }
    }

    if (b)
      continue;

    long long m = std::sqrt(n);

    for (long long i = pri[cnt - 1] + 2; i <= m; i += 2) {
      if (n % i == 0) {
        b = true;
        break;
      }
    }

    if (!b) {
      std::cout << n << '\n';
    }

    std::cin >> std::ws;
  }

  return 0;
}