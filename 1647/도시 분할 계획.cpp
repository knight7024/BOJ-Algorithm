#include <bits/stdc++.h>
using namespace std;

int parent[100001];

int getParent(int n) {
    if (!parent[n]) return n;
    return parent[n] = getParent(parent[n]);
}

void setParent(int a, int b) {
    if (a > b) swap(a, b);
    a = getParent(a);
    b = getParent(b);
    parent[b] = a;
}

bool isCyclic(int a, int b) {
    return getParent(a) == getParent(b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<tuple<int, int, int>> allNodes(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
        allNodes.emplace_back(a, b, c);
    }

    sort(allNodes.begin(), allNodes.end(), [](tuple<int, int, int>& a, tuple<int, int, int>& b) {
        if (get<2>(a) == get<2>(b)) {
            if (get<0>(a) == get<0>(b)) return get<1>(a) < get<1>(b);
            return get<0>(a) < get<0>(b);
        }
        return get<2>(a) < get<2>(b);
    });

    long allDist = 0;
    int biggestDist = 0;
    for (auto& node : allNodes) {
        int u, v, dist;
        tie(u, v, dist) = node;
        if (isCyclic(u, v)) continue;
        setParent(u, v);
        allDist += dist;
        biggestDist = dist;
    }

    cout << allDist - biggestDist;

    return 0;
}
