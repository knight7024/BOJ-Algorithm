#include <bits/stdc++.h>
using namespace std;

vector<int> energy;
vector<vector<pair<int, int>>> adj;
int closestRoom[100001];
bool visited[100001];
vector<pair<int, int>> dfsStack;

void dfs(int node, int sum) {
    visited[node] = true;
    dfsStack.emplace_back(sum, node);
    int pos = lower_bound(dfsStack.begin(), dfsStack.end(), sum - energy[node], [&](const pair<int, int>& a, const int b) {
        return a.first < b;
    }) - dfsStack.begin();
    closestRoom[node] = dfsStack[pos].second;
    for (auto& next : adj[node]) {
        if (visited[next.first]) continue;
        dfs(next.first, sum + next.second);
    }
    dfsStack.pop_back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    energy.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> energy[i];
    }

    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        cout << closestRoom[i] << ' ';
    }
    
    return 0;
}
