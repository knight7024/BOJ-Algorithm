#include <bits/stdc++.h>
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct Coor {
    int y, x;
    int nowYear;
    Coor() {}
    Coor(int y, int x, int nowYear): y(y), x(x), nowYear(nowYear) {}
    bool operator==(const Coor& a) const { return y == a.y && x == a.x; }
    bool operator!=(const Coor& a) const { return !(*this == a); }
};

int parent[100001];

int getParent(int x) {
    if (parent[x] == -1) return x;
    return parent[x] = getParent(parent[x]);
}

void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a < b) parent[b] = a;
    else if (a > b) parent[a] = b;
}

int visited[2001][2001];
int maxYear[2001][2001];
bool isConnected[2001][2001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    queue<Coor> bfs;
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        bfs.emplace(n - y, x - 1, 0);
        visited[n - y][x - 1] = i;
        maxYear[n - y][x - 1] = 0;
    }

    memset(parent, -1, sizeof parent);

    while (!bfs.empty()) {
        int t = bfs.size();
        while (t--) {
            auto front = bfs.front();
            bfs.pop();
    
            int prevParent = getParent(visited[front.y][front.x]);
            for (int d = 0; d < 4; d++) {
                int ny = dy[d] + front.y;
                int nx = dx[d] + front.x;
                if (ny < 0 or ny >= n or nx < 0 or nx >= n or !visited[ny][nx]) continue;

                int nowParent = getParent(visited[ny][nx]);
                if (prevParent != nowParent) {
                    isConnected[ny][nx] = true;
                    unionParent(prevParent, nowParent);
                }
            }

            bfs.emplace(front);
        }

        t = bfs.size();
            while (t--) {
            auto front = bfs.front();
            bfs.pop();
    
            int prevParent = getParent(visited[front.y][front.x]);
            for (int d = 0; d < 4; d++) {
                int ny = dy[d] + front.y;
                int nx = dx[d] + front.x;
                if (ny < 0 or ny >= n or nx < 0 or nx >= n) continue;
    
                if (visited[ny][nx]) {
                    int nowParent = getParent(visited[ny][nx]);
                    if (prevParent != nowParent) {
                        isConnected[ny][nx] = true;
                        maxYear[ny][nx] = front.nowYear + 1;
                        unionParent(prevParent, nowParent);
                    }
                }
                else {
                    bfs.emplace(ny, nx, front.nowYear + 1);
                    visited[ny][nx] = prevParent;
                    maxYear[ny][nx] = front.nowYear + 1;
                }
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!isConnected[i][j]) continue;
            answer = max(answer, maxYear[i][j]);
        }
    }

    cout << answer;
    
    return 0;
}
