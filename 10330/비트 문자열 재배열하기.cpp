#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int start = 0;
    int q;
    for (int i = 0; i < n; i++) {
        cin >> q;
        (start <<= 1) |= q;
    }

    int dest1 = 0;
    for (int i = 0; i < m; i++) {
        cin >> q;
        for (int j = 0; j < q; j++) (dest1 <<= 1) |= ~i & 1;
    }
    int dest2 = dest1 ^ ((1 << n) - 1);

    queue<pair<int, int>> bfs;
    int visited[1 << 15];
    memset(visited, INF, sizeof(visited));
    
    bfs.emplace(start, 0);
    visited[start] = 0;

    while (!bfs.empty()) {
        auto front = bfs.front();
        bfs.pop();

        int window = 3;
        for (int i = 0; i < n - 1; i++) {
            int inversed = front.first ^ window;
            if (inversed == (front.first | window) or inversed < 0 or inversed == front.first - window) {
                window <<= 1;
                continue;
            }
            window <<= 1;
            if (visited[inversed] <= front.second + 1) continue;
            bfs.emplace(inversed, front.second + 1);
            visited[inversed] = front.second + 1;
        }
    }

    cout << min(visited[dest1], visited[dest2]);
    
    return 0;
}
