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

struct node{
    int x, y;
    node(){}
    node(int _x = 0,int _y = 0): x(_x), y(_y){}
};

int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int n;
vector<string> graph;
vector<vector<int>> vis;

int solve() {
    queue<node> Q;
    for(int i = 0;i < n;++i){
        for(int j = 0;j < n;++j){
            if(graph[i][j] == '#') Q.push(node(i,j));
            vis[i][j] = 0;
        }
    }
    
    if(Q.size() == n * n || Q.empty()) return -1;

    int dis = 0;
    while(!Q.empty()){
        int size = Q.size();
        while(size-- > 0){
            node cur = Q.front();
            Q.pop();
            for(int i = 0;i < 4;i++){
                int nextX = cur.x + dir[i][0];
                int nextY = cur.y + dir[i][1];
                if(nextX > -1 && nextX < n && nextY > -1 && nextY < n && graph[nextX][nextY] == '.' && !vis[nextX][nextY]){
                    vis[nextX][nextY] = 1;
                    Q.push(node(nextX,nextY));
                }
            }
        }
        if(!Q.empty()) dis += 1;
    }
    return dis;
}

int main(void) {
    cin >> n;
    string line;
    vis.resize(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        cin >> line;
        graph.push_back(line);
    }

    cout << solve();
    return 0;
}