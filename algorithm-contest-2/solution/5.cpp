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

int dp[1005][5][1005];
int n, K, a[1005];

int main(void) {
    // freopen("3.in", "r", stdin);
    cin >> n >> K;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 0; i < 1005; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 1005; k++)
                dp[i][j][k] = INT_MIN;

    dp[0][0][0] = 0;
    
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 4; j++)
            for (int k = 0; k < K; k++) {
                if (j == 0) dp[i][j][k] = dp[i - 1][j][k];
                else dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - 1][((k - a[i]) % K + K) % K] + a[i]);
            }
                

    cout << dp[n][4][0];
    return 0;
}