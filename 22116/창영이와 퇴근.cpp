#include <bits/stdc++.h>
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct Coor {
    int y, x;
    int diff;
    Coor() {}
    Coor(int y, int x, int diff): y(y), x(x), diff(diff) {}
    bool operator<(const Coor& a) const { return diff < a.diff; }
    bool operator>(const Coor& a) const { return diff > a.diff; }
    bool operator==(const Coor& a) const { return y == a.y && x == a.x; }
    bool operator!=(const Coor& a) const { return !(*this == a); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    int board[1000][1000];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    priority_queue<Coor, vector<Coor>, greater<>> pq;
    bool visited[1000][1000] {};

    pq.emplace(0, 0, 0);
    visited[0][0] = true;

    int answer = 0;
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        answer = max(answer, top.diff);
        if (top.y == n - 1 and top.x == n - 1) break;

        visited[top.y][top.x] = true;
        for (int d = 0; d < 4; d++) {
            int ny = dy[d] + top.y;
            int nx = dx[d] + top.x;
            if (ny < 0 or ny >= n or nx < 0 or nx >= n or visited[ny][nx]) continue;
            pq.emplace(ny, nx, abs(board[top.y][top.x] - board[ny][nx]));
        }
    }

    cout << answer;
    
    return 0;
}
