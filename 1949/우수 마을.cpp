#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
vector<int> people;
vector<vector<int>> adj;
bool visited[10001];
long dp[10001][2];

long dfs(int node, bool isGreat) {
	if (adj[node].empty()) return isGreat ? people[node] : 0;
	long& ret = dp[node][isGreat];
	if (ret != -1) return ret;

	visited[node] = true;
	ret = 0;
	if (!isGreat) {
		for (int child : adj[node]) {
			if (visited[child]) continue;
			ret += max(dfs(child, 0), dfs(child, 1));
		}
	}
	else {
		long resultY = 0;
		long resultN = 0;
		for (int child : adj[node]) {
			if (visited[child]) continue;
			resultY += dfs(child, 1);
			resultN += dfs(child, 0);
		}
		ret = max(resultN + people[node], resultY);
	}
	visited[node] = false;

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;

	people.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> people[i];
	}

	adj.resize(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	memset(dp, -1, sizeof(dp));

	cout << max(dfs(1, 0), dfs(1, 1));

	return 0;
}
