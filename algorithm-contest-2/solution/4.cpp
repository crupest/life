#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <unordered_map>
#define x first
#define y second
#define pub push_back
#define MP make_pair
#define LL long long
using namespace std;
typedef pair<int, int> PII;

const int MAXN = 1e5 + 5;
int n, k, h[MAXN], w[MAXN];

bool check(int m) {
    if (m == 0) return true;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += (h[i] / m) * (w[i] / m);
    }
    return cnt >= k;
}

int main(void) {
    cin >> n >> k;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
        scanf("%d", &w[i]);
        mx = max(mx, max(h[i], w[i]));
    }

    int l = 0, r = mx;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (check(m)) l = m;
        else r = m - 1;
    }
    cout << r;
    return 0;
}