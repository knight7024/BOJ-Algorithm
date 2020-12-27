#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#define endl '\n'
using namespace std;

vector <vector<int>> adj;
vector <vector<int>> revAdj;
stack <int> topo;
bool visited[10001];

void dfs(int startNode) {
    visited[startNode] = true;
    for (int & i: adj[startNode]) {
        if (!visited[i]) dfs(i);
    }
    topo.emplace(startNode);
}

void kosaraju(int startNode, int sccIdx, vector < vector < int >> & scc) {
    visited[startNode] = true;
    scc[sccIdx].push_back(startNode);
    for (int & i: revAdj[startNode]) {
        if (!visited[i]) kosaraju(i, sccIdx, scc);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n >> t;
    adj.resize(n + 1);
    revAdj.resize(n + 1);

    int a, b;
    while (cin >> a >> b) {
        adj[a].emplace_back(b);
        revAdj[b].emplace_back(a);
    }

    // SCC Algorithm
    // 1. 모든 정점에 대해 DFS 수행하면서 위상정렬
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i);
    }

    memset(visited, 0, sizeof(visited));

    // 2. 역그래프에 대해 DFS 수행
    vector<vector<int>> scc;
    int sccIdx = 0;
    while (!topo.empty()) {
        int top = topo.top();
        topo.pop();
        if (!visited[top]) {
            sccIdx++;
            scc.resize(sccIdx);
            kosaraju(top, sccIdx - 1, scc);
        }
    }

    cout << sccIdx << endl;

    for (auto & i: scc) sort(i.begin(), i.end());
    sort(scc.begin(), scc.end());

    for (auto & i: scc) {
        for (auto & j: i) {
            cout << j << ' ';
        }
        cout << -1 << endl;
    }

    return 0;
}
