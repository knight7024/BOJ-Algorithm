#include <bits/stdc++.h>
using namespace std;

struct Coor {
    int y, x;
    Coor() {}
    Coor(int y, int x): y(y), x(x) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int w, h;
    cin >> w >> h;

    bool board[102][102] {};
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cin >> board[i][j];
        }
    }

    queue<Coor> bfs;
    bool visited[102][102] {};

    bfs.emplace(0, 0);
    visited[0][0] = true;

    auto doWork = [&](Coor& a, int& borderCount) -> void {
        if (a.y >= 0 and a.y <= h + 1 and a.x >= 0 and a.x <= w + 1) {
            borderCount += board[a.y][a.x];
            if (!board[a.y][a.x] and !visited[a.y][a.x]) {
                bfs.emplace(a);
                visited[a.y][a.x] = true;
            }
        }
    };

    int answer = 0;
    while (!bfs.empty()) {
        auto front = bfs.front();
        bfs.pop();

        int borderCount = 0;
        // 좌측 상단
        Coor nextCoor = (front.y & 1) ? Coor(front.y - 1, front.x) : Coor(front.y - 1, front.x - 1);
        doWork(nextCoor, borderCount);
        // 우측 상단
        nextCoor = (front.y & 1) ? Coor(front.y - 1, front.x + 1) : Coor(front.y - 1, front.x);
        doWork(nextCoor, borderCount);
        // 좌측
        nextCoor = Coor(front.y, front.x - 1);
        doWork(nextCoor, borderCount);
        // 우측
        nextCoor = Coor(front.y, front.x + 1);
        doWork(nextCoor, borderCount);
        // 좌측 하단
        nextCoor = (front.y & 1) ? Coor(front.y + 1, front.x) : Coor(front.y + 1, front.x - 1);
        doWork(nextCoor, borderCount);
        // 우측 하단
        nextCoor = (front.y & 1) ? Coor(front.y + 1, front.x + 1) : Coor(front.y + 1, front.x);
        doWork(nextCoor, borderCount);
        
        answer += borderCount;
    }

    cout << answer;
    
    return 0;
}
