#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int prevNode[1001];

void dfs(int n) {
    if (prevNode[n] != 1) dfs(prevNode[n]);
    cout << n << ' ';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    int m;
    cin >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    int indegree[1001] {};
    for (int i = 0; i < m; i++) {
        int p, q, r;
        cin >> p >> q >> r;
        adj[p].emplace_back(q, r);
        indegree[q]++;
    }

    queue<pair<int, int>> bfs;
    bfs.emplace(1, 0);

    int dp[1001] {};
    while (!bfs.empty()) {
        auto front = bfs.front();
        bfs.pop();

        for (auto& p : adj[front.first]) {
            if (indegree[p.first] > 0 and dp[p.first] < front.second + p.second) {
                dp[p.first] = front.second + p.second;
                prevNode[p.first] = front.first;
            }
            if (!--indegree[p.first]) bfs.emplace(p.first, dp[p.first]);
        }
    }

    cout << dp[1] << endl << 1 << ' ';

    dfs(1);
    
    return 0;
}
