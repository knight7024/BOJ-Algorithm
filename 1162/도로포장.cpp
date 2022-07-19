#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int n, m, k;
vector<vector<pair<int, int>>> adj;
long dp[10001][21];

long dijkstra(int start) {
    priority_queue<tuple<long, int, int>, vector<tuple<long, int, int>>, greater<>> pq;
    fill(&dp[0][0], &dp[10000][21], LONG_MAX);

    pq.emplace(0, start, 0);
    dp[start][0] = 0;

    while (!pq.empty()) {
        auto [nowDist, nowNode, pavedRoads] = pq.top();
        pq.pop();
        if (dp[nowNode][pavedRoads] < nowDist) continue;

        for (auto& [nextNode, nextDist] : adj[nowNode]) {
            if (dp[nextNode][pavedRoads] > nowDist + nextDist) {
                pq.emplace(nowDist + nextDist, nextNode, pavedRoads);
                dp[nextNode][pavedRoads] = nowDist + nextDist;
            }
            if (pavedRoads < k and dp[nextNode][pavedRoads + 1] > nowDist) {
                pq.emplace(nowDist, nextNode, pavedRoads + 1);
                dp[nextNode][pavedRoads + 1] = nowDist;
            }
        }
    }

    return *min_element(dp[n], dp[n] + k + 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].emplace_back(v, d);
        adj[v].emplace_back(u, d);
    }

    cout << dijkstra(1);
    
    return 0;
}
