#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

vector<int> parent;

int getParent(int node) {
    if (parent[node] == node) return node;
    return parent[node] = getParent(parent[node]);
}

void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a > b) parent[a] = b;
    else parent[b] = a;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < n; i++) parent.push_back(i);

    int answer = INF;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (getParent(u) == getParent(v)) answer = min(answer, i + 1);
        unionParent(u, v);
    }

    cout << (answer == INF ? 0 : answer);

    return 0;
}
