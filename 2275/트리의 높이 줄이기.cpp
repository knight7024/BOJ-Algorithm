#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int n, h;
int root;
vector<vector<pair<int, int>>> adj;
int answer;

int dfs(int nowNode, int nowDist, int edgeDist) {
    int sum = max(nowDist - h, 0);
    for (auto& [nextNode, nextDist] : adj[nowNode]) {
        sum = max(sum, dfs(nextNode, nowDist + nextDist, nextDist));
    }
    if (nowDist - edgeDist >= sum) return sum;
    answer += sum - nowDist + edgeDist;
    return nowDist - edgeDist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> h;

    adj.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int p, d;
        cin >> p >> d;
        if (!p and !d) root = i;
        adj[p].emplace_back(i, d);
    }

    dfs(root, 0, 0);

    cout << answer;
    
    return 0;
}
