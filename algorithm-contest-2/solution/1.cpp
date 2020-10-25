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

int x, y;

int main(void) {
    cin >> x >> y;
    int ans = x;
    while (x >= y) {
        ans += x / y;
        x = x / y + x % y;
    }
    cout << ans;
    return 0;
}