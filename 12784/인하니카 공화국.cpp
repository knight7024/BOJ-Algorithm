#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define ROOT 1
using namespace std;

const int INF = 0x3f3f3f3f;

int dynamite[1001][1001];
bool visited[1001];
int dp[1001][2];

int dfs(int node, bool bomb, int from, vector<vector<int>>& adj) {
	if (node != ROOT && adj[node].size() == 1) return dynamite[from][node];
	int& ret = dp[node][bomb];
	if (ret != INF) return ret;

	// 현재 노드로 연결된 다리를 폭파시킨다면
	if (bomb) return dynamite[from][node];
	else {
		visited[node] = true;
		ret = 0;
		for (int& next : adj[node]) {
			if (visited[next]) continue;
			ret += min(dfs(next, 0, node, adj), dfs(next, 1, node, adj));
		}
		visited[node] = false;
	}

	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int t;
	cin >> t;

	while (t--) {
		int n, m;
		cin >> n >> m;

		vector<vector<int>> adj(n + 1);
		for (int i = 0; i < m; i++) {
			int a, b, d;
			cin >> a >> b >> d;
			adj[a].push_back(b);
			adj[b].push_back(a);
			dynamite[a][b] = dynamite[b][a] = d;
		}

		memset(dp, INF, sizeof(dp));

		cout << dfs(ROOT, 0, ROOT, adj) << '\n';
		memset(dynamite, 0, sizeof(dynamite));
		memset(visited, 0, sizeof(visited));
	}
	return 0;
}
