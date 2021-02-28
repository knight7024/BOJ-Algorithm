#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, n, h;
    cin >> m >> n >> h;

    int map[10001][101];
    queue<pair<int, int>> box;
    for (int i = 0; i < n * h; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) box.emplace(i, j);
        }
    }

    const int dy[] = {1, 0, -1, 0, -n, n};
    const int dx[] = {0, 1, 0, -1, 0, 0};

    while (!box.empty()) {
        auto front = box.front();
        box.pop();

        int y = front.first;
        int x = front.second;
        for (int i = 0; i < 6; i++) {
            int ny = dy[i] + y;
            int nx = dx[i] + x;
            // 상자 밖의 범위면 넘어간다.
            if (ny < 0 || nx < 0 || nx >= m || ny >= n * h) continue;
            // 층을 넘어가는 단계가 아닌데 넘어가면
            if ((i == 0 || i == 2) && (y / n != ny / n)) continue;
            // 익지 않은 토마토가 없으면 넘어간다.
            if (map[ny][nx]) continue;

            box.emplace(ny, nx);
            map[ny][nx] = map[y][x] + 1;
        }
    }

    int answer = 0;
    for (int i = 0; i < n * h; i++) {
        for (int j = 0; j < m; j++) {
            if (!map[i][j]) {
                cout << -1;
                return 0;
            }
            answer = max(answer, map[i][j]);
        }
    }

    cout << answer - 1;

    return 0;
}
