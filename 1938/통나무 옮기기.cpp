#include <bits/stdc++.h>
using namespace std;

const int dy[] {-1, 1, 0, 0};
const int dx[] {0, 0, -1, 1};

const int INF = 0x7f7f7f7f;

struct Coor {
    int y, x;
    Coor() {}
    Coor(int y, int x): y(y), x(x) {}
};

struct Info {
    Coor center;
    bool isVertical;
    int moveCount;
    Info() {}
    Info(Coor center, bool isVertical, int moveCount): center(center), isVertical(isVertical), moveCount(moveCount) {}
};

int n;
char board[51][51];

bool canMove(Coor coor) {
    return coor.y >= 0 and coor.y < n and coor.x >= 0 and coor.x < n and board[coor.y][coor.x] != '1';
}

bool isValid(Coor& coor, bool isVertical) {
    if (isVertical) return canMove(coor) & canMove({coor.y - 1, coor.x}) & canMove({coor.y + 1, coor.x});
    return canMove(coor) & canMove({coor.y, coor.x - 1}) & canMove({coor.y, coor.x + 1});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }

    vector<Coor> sPos, ePos;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'B') sPos.emplace_back(i, j);
            else if (board[i][j] == 'E') ePos.emplace_back(i, j);
        }
    }

    queue<Info> bfs;
    int dp[51][51][2];
    memset(dp, INF, sizeof(dp));

    bfs.emplace(sPos[1], sPos[0].x == sPos[1].x, 0);
    dp[sPos[1].y][sPos[1].x][sPos[0].x == sPos[1].x] = 0;

    while (!bfs.empty()) {
        auto front = bfs.front();
        bfs.pop();

        for (int d = 0; d < 4; d++) {
            Coor nextCoor = {front.center.y + dy[d], front.center.x + dx[d]};
            if (isValid(nextCoor, front.isVertical) and dp[nextCoor.y][nextCoor.x][front.isVertical] > front.moveCount + 1) {
                bfs.emplace(nextCoor, front.isVertical, front.moveCount + 1);
                dp[nextCoor.y][nextCoor.x][front.isVertical] = front.moveCount + 1;
            }
        }
        
        Coor nextCoor = {front.center.y, front.center.x};
        bool canTurn = true;
        for (int y = nextCoor.y - 1; y <= nextCoor.y + 1; y++) {
            for (int x = nextCoor.x - 1; x <= nextCoor.x + 1; x++) {
                if (!canMove({y, x})) {
                    canTurn = false;
                    break;
                }
            }
            if (!canTurn) break;
        }
        if (canTurn and isValid(nextCoor, front.isVertical ^ 1) and dp[nextCoor.y][nextCoor.x][front.isVertical ^ 1] > front.moveCount + 1) {
            bfs.emplace(nextCoor, front.isVertical ^ 1, front.moveCount + 1);
            dp[nextCoor.y][nextCoor.x][front.isVertical ^ 1] = front.moveCount + 1;
        }
    }

    int result = dp[ePos[1].y][ePos[1].x][ePos[0].x == ePos[1].x];
    cout << (result == INF ? 0 : result);
    
    return 0;
}
