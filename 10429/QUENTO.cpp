#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct Coor {
    int y, x;
    int sum;
    int visitedSet;
    char prevOp;
    string path;
    Coor() {}
    Coor(int y, int x): y(y), x(x) {}
    Coor(int y, int x, int sum, int visitedSet, char prevOp, string path): y(y), x(x), sum(sum), visitedSet(visitedSet), prevOp(prevOp), path(path) {}
};

char board[3][3];

int main() {
    cin.tie(0)->sync_with_stdio(0);
  
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> board[i][j];
        }
    }

    queue<Coor> bfs;
    bfs.emplace(0, 0, board[0][0] - '0', 1, -1, "0"); bfs.emplace(0, 2, board[0][2] - '0', 4, -1, "2");
    bfs.emplace(1, 1, board[1][1] - '0', 16, -1, "4"); bfs.emplace(2, 0, board[2][0] - '0', 64, -1, "6");
    bfs.emplace(2, 2, board[2][2] - '0', 256, -1, "8");

    while (!bfs.empty()) {
        auto front = bfs.front();
        bfs.pop();
        if (__builtin_popcount(front.visitedSet) >= 2 * m - 1) {
            if (front.sum == n) {
                cout << 1 << endl;
                for (int i = 0; i < 2 * m - 1; i++) {
                    cout << (front.path[i] - '0') / 3 << ' ' << (front.path[i] - '0') % 3 << endl;
                }
                exit(0);
            }
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int ny = front.y + dy[i];
            int nx = front.x + dx[i];
            if (ny >= 3 or ny < 0 or nx >= 3 or nx < 0) continue;
            if (front.visitedSet & (1 << (ny * 3 + nx))) continue;

            int nextVisitedSet = front.visitedSet | (1 << (ny * 3 + nx));
            if (isdigit(board[ny][nx])) {
                int nextSum = front.sum;
                nextSum += front.prevOp == '-' ? -(board[ny][nx] - '0') : board[ny][nx] - '0';
                bfs.emplace(ny, nx, nextSum, nextVisitedSet, -1, front.path + to_string(ny * 3 + nx));
            }
            else {
                bfs.emplace(ny, nx, front.sum, nextVisitedSet, board[ny][nx], front.path + to_string(ny * 3 + nx));
            }
        }
    }

    cout << 0;
    
    return 0;
}
