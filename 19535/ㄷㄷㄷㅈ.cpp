#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> tree;
bool visited[300001];
long d, g;

void dfs(int node) {
    visited[node] = true;

    if (tree[node].size() >= 3) g += tree[node].size() * (tree[node].size() - 1) * (tree[node].size() - 2) / 6;
    if (tree[node].size() >= 2) {
        for (int i : tree[node]) {
            if (!visited[i] && tree[i].size() >= 2) {
                d += (tree[node].size() - 1) * (tree[i].size() - 1);
            }
        }
    }

    for (int i : tree[node]) if (!visited[i]) dfs(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    tree.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1);

    cout << (d == g * 3 ? "DUDUDUNGA" : d > g * 3 ? "D" : "G");

    return 0;
}
