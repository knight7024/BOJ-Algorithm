#include <bits/stdc++.h>
using namespace std;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int map[301][301];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }

    int answer = 0;
    queue<tuple<int, int, int>> waves;
    while (1) {
        queue<pair<int, int>> bfs;
        bool visited[301][301] {};

        int glacier = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] <= 0 || visited[i][j]) continue;

                if (++glacier >= 2) {
                    cout << answer;
                    exit(0);
                }
                bfs.emplace(i, j);
                visited[i][j] = true;

                while (!bfs.empty()) {
                    auto front = bfs.front();
                    bfs.pop();

                    int wave = 0;
                    for (int d = 0; d < 4; d++) {
                        int ny = front.first + dy[d];
                        int nx = front.second + dx[d];
                        if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
                        if (map[ny][nx] <= 0) {
                            wave++;
                            continue;
                        }
                        if (visited[ny][nx]) continue;

                        bfs.emplace(ny, nx);
                        visited[ny][nx] = true;
                    }

                    waves.emplace(front.first, front.second, wave);
                }
            }
        }
        if (!glacier) break;

        while (!waves.empty()) {
            auto front = waves.front();
            waves.pop();
            map[get<0>(front)][get<1>(front)] -= get<2>(front);
        }
        answer++;
    }

    cout << 0;

    return 0;
}
