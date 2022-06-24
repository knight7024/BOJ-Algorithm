#include <bits/stdc++.h>
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int n, m;
char dirMap[1001][1001];
int parent[1000001];

int findParent(int x) {
    if (parent[x] == -1) return x;
    return parent[x] = findParent(parent[x]);
}

void unionParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a < b) parent[b] = a;
    else parent[a] = b;
}

int coor2num(int y, int x) {
    return y * m + x;
}

int dir2num(char c) {
    if (c == 'U') return 0;
    if (c == 'R') return 1;
    if (c == 'D') return 2;
    return 3;
}

void dfs(int y, int x) {
    int d = dir2num(dirMap[y][x]);
    int ny = dy[d] + y;
    int nx = dx[d] + x;
    
    int nowNum = coor2num(y, x), nextNum = coor2num(ny, nx);
    if (findParent(nowNum) == findParent(nextNum)) return;
    unionParent(nowNum, nextNum);
    dfs(ny, nx);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> dirMap[i][j];
        }
    }

    memset(parent, -1, sizeof(parent));

    set<int> answer;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (parent[coor2num(i, j)] != -1) continue;
            dfs(i, j);
            answer.insert(findParent(coor2num(i, j)));
        }
    }

    cout << answer.size();
    
    return 0;
}
