#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <climits>
#define x first
#define y second
#define pub push_back
#define mp make_pair
#define ll long long
using namespace std;
typedef pair<int, int> PII;

const int MAXN = 1e5 + 5;
int n, a[MAXN];

int main(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    
    int l = 1, r = n;
    ll ans = 0;
    
    while (l < r) {
        ans += (a[r--] - a[l++]);
    }
    cout << ans;
    return 0;
}