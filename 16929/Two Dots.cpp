#include <bits/stdc++.h>
using namespace std;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int n, m;
char board[51][51];
int visited[51][51];

bool dfs(int y, int x, int depth) {
    visited[y][x] = depth;
    bool result = false;
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 || ny >= n || nx < 0 || nx >= m || board[y][x] != board[ny][nx]) continue;
        if (depth >= 4 && visited[ny][nx] == 1) return true;
        else if (visited[ny][nx]) continue;
        if (result |= dfs(ny, nx, depth + 1)) break;
    }
    visited[y][x] = 0;
    
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    bool answer = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dfs(i, j, 1)) {
                answer = true;
                break;
            }
        }
    }

    cout << (answer ? "Yes" : "No");
    
    return 0;
}
