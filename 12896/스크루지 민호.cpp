#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

vector<vector<int>> adj;

bool visited[100001];
int farthestNode = -1, farthestDistance = 0;

void dfs(int node, int depth) {
    visited[node] = true;
    if (farthestDistance < depth) {
        farthestNode = node;
        farthestDistance = depth;
    }
    for (int next : adj[node]) {
        if (visited[next]) continue;
        dfs(next, depth + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    memset(visited, 0, sizeof(visited));
    farthestDistance = 0;
    dfs(farthestNode, 0);

    cout << (farthestDistance & 1 ? farthestDistance / 2 + 1 : farthestDistance / 2);
    
    return 0;
}
