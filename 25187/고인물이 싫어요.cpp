#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

vector<vector<int>> adj;
vector<int> tanks;
int water[100001];
int parent[100001];

int getParent(int x) {
    if (parent[x] == -1) return x;
    return parent[x] = getParent(parent[x]);
}

void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a < b) parent[b] = a;
    else if (a > b) parent[a] = b;
}

void dfs(int node) {
    for (int next : adj[node]) {
        if (getParent(node) == getParent(next)) continue;
        unionParent(node, next);
        water[getParent(node)] += tanks[next] * 2 - 1;
        dfs(next);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    tanks.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> tanks[i];
    }

    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(parent, -1, sizeof parent);
    for (int i = 1; i <= n; i++) {
        if (getParent(i) != i) continue;
        water[i] += tanks[i] * 2 - 1;
        dfs(i);
    }

    while (q--) {
        int k;
        cin >> k;
        cout << (water[getParent(k)] > 0) << ' ';
    }

    return 0;
}
