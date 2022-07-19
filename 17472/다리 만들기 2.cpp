#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int INF = 0x7f7f7f7f;

const int dy[] {-1, 1, 0, 0};
const int dx[] {0, 0, -1, 1};

int n, m;
bool mapBoard[10][10];
int islandNum = 1;
int mapByNum[10][10];
vector<tuple<int, int, int>> bridges;

void dfs(int y, int x, int dir, int prevIsland, int length) {
    if (y < 0 or y >= n or x < 0 or x >= m) return;
    if (mapByNum[y][x] == prevIsland) return;
    if (mapByNum[y][x]) {
        if (length >= 2) bridges.emplace_back(prevIsland, mapByNum[y][x], length);
        return;
    }
    dfs(y + dy[dir], x + dx[dir], dir, prevIsland, length + 1);
}

void countBridges() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!mapByNum[i][j]) continue;
            for (int d = 0; d < 4; d++) {
                int ny = dy[d] + i;
                int nx = dx[d] + j;
                if (ny < 0 or ny >= n or nx < 0 or nx >= m) continue;
                dfs(ny, nx, d, mapByNum[i][j], 0);
            }
        }
    }
}

void fillIslandsByNum() {
    queue<tuple<int, int, int>> bfs;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!mapBoard[i][j] or mapByNum[i][j]) continue;

            mapByNum[i][j] = islandNum;
            bfs.emplace(i, j, islandNum++);
            while (!bfs.empty()) {
                auto [y, x, num] = bfs.front();
                bfs.pop();

                for (int d = 0; d < 4; d++) {
                    int ny = dy[d] + y;
                    int nx = dx[d] + x;
                    if (ny < 0 or ny >= n or nx < 0 or nx >= m) continue;
                    if (!mapBoard[ny][nx] or mapByNum[ny][nx]) continue;
                    mapByNum[ny][nx] = num;
                    bfs.emplace(ny, nx, num);
                }
            }
        }
    }
}

int parent[10];

int getParent(int x) {
    if (parent[x] == -1) return x;
    return getParent(parent[x]);
}

bool allConnected() {
    for (int i = 2; i < islandNum; i++) {
        if (getParent(i) != getParent(1)) {
            return false;
        }
    }
    return true;
}

int answer = INF;

void backtracking(int pos, int sum) {
    if (pos >= bridges.size()) {
        if (allConnected()) answer = min(answer, sum);
        return;
    }
    auto& [u, v, l] = bridges[pos];
    int uParent = getParent(u), vParent = getParent(v);
    if (uParent != vParent) {
        if (uParent < vParent) parent[vParent] = uParent;
        else parent[uParent] = vParent;
        backtracking(pos + 1, sum + l);
        parent[uParent] = parent[vParent] = -1;
    }
    
    backtracking(pos + 1, sum);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mapBoard[i][j];
        }
    }

    fillIslandsByNum();
    countBridges();

    memset(parent, -1, sizeof parent);
    backtracking(0, 0);

    cout << (answer == INF ? -1 : answer);
    
    return 0;
}
