#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> adj;
bool visited[1000001];
int dp[1000001][2];

int dfs(int node, bool isEA) {
	if (adj[node].empty()) return isEA;
	int& ret = dp[node][isEA];
	if (ret != -1) return ret;

	visited[node] = true;
	ret = isEA;
	if (isEA) {
		for (int child : adj[node]) {
			if (visited[child]) continue;
			ret += min(dfs(child, 0), dfs(child, 1));
		}
	}
	else {
		for (int child : adj[node]) {
			if (visited[child]) continue;
			ret += dfs(child, 1);
		}
	}
	visited[node] = false;

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;

	adj.resize(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	memset(dp, -1, sizeof(dp));

	cout << min(dfs(1, 0), dfs(1, 1));

	return 0;
}
