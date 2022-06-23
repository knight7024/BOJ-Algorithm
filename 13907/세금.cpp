#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

struct Vertex {
    int node;
    int edgeCount;
    long dist;
    Vertex() {}
    Vertex(int node, int edgeCount, long dist): node(node), edgeCount(edgeCount), dist(dist) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;
    
    int s, d;
    cin >> s >> d;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }

    long dist[1001][1001];
    fill(&dist[0][0], &dist[1000][1001], LONG_MAX);

    queue<Vertex> bfs;
    bfs.emplace(s, 0, 0);

    while (!bfs.empty()) {
        auto front = bfs.front();
        bfs.pop();
        if (front.edgeCount > n) continue;
        if (front.dist > dist[front.node][front.edgeCount]) continue;
        if (front.node == d) continue;

        for (auto& next : adj[front.node]) {
            long nextDist = front.dist + next.second;
            int nextEdgeCount = front.edgeCount + 1;
            if (nextDist >= dist[next.first][nextEdgeCount]) continue;
            bfs.emplace(next.first, nextEdgeCount, nextDist);
            dist[next.first][nextEdgeCount] = nextDist;
        }
    }

    long answer = LONG_MAX;
    vector<pair<long, int>> arr;
    for (int i = 1; i <= n; i++) {
        if (dist[d][i] == LONG_MAX) continue;
        arr.emplace_back(dist[d][i], i);
        answer = min(answer, dist[d][i]);
    }
    cout << answer << endl;
    
    for (int i = 0; i < k; i++) {
        int p;
        cin >> p;

        answer = LONG_MAX;
        for (auto& j : arr) {
            answer = min(answer, j.first += p * j.second);
        }
        cout << answer << endl;
    }
    
    return 0;
}
