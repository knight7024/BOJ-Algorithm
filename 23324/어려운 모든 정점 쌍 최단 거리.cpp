#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

vector<vector<pair<int, int>>> adj;

void dijkstra(int start, int dist[]) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    pq.emplace(0, start);
    dist[start] = 0;

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int nowNode = top.second, nowDist = top.first;
        if (nowDist > dist[nowNode]) continue;

        for (auto& next : adj[nowNode]) {
            int nextNode = next.first, nextDist = nowDist + next.second;
            if (nextDist >= dist[nextNode]) continue;
            pq.emplace(nextDist, nextNode);
            dist[nextNode] = nextDist;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    adj.resize(n + 1);
    int start1, start2;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v, i == k);
        adj[v].emplace_back(u, i == k);
        if (i == k) start1 = u, start2 = v;
    }

    int dist1[100001]; memset(dist1, INF, sizeof dist1);
    int dist2[100001]; memset(dist2, INF, sizeof dist2);
    dijkstra(start1, dist1); dijkstra(start2, dist2);

    long answer = 0;
    long cnt10 = 0, cnt01 = 0;
    for (int i = n; i >= 1; i--) {
        if (dist1[i] and !dist2[i]) {
            answer += cnt01;
            ++cnt10;
        }
        else if (!dist1[i] and dist2[i]) {
            answer += cnt10;
            ++cnt01;
        }
    }

    cout << answer;
    
    return 0;
}
