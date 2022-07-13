#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

int n, m;
int graph[1001][1001];
bool visited[1001];
vector<pair<int, int>> answer;

int prim(int start) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.emplace(0, start, start);

    int fullDist = 0;
    while (!pq.empty()) {
        auto [nowDist, prevNode, nowNode] = pq.top();
        pq.pop();
        if (visited[nowNode]) continue;

        visited[nowNode] = true;
        if (nowDist) fullDist += nowDist, answer.emplace_back(prevNode, nowNode);
        for (int nextNode = 2; nextNode <= n; nextNode++) {
            if (visited[nextNode] or nowNode == nextNode) continue;
            pq.emplace(graph[nowNode][nextNode], nowNode, nextNode);
        }
    }

    return fullDist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    memset(graph, INF, sizeof graph);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x][y] = graph[y][x] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j or graph[i][j] != INF) {
                int x; cin >> x;
                continue;
            }
            cin >> graph[i][j];
        }
    }

    cout << prim(2) << ' ' << answer.size() << endl;
    for (auto& [x, y] : answer) cout << x << ' ' << y << endl;
    
    return 0;
}
