#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <algorithm>
#define endl '\n'

using namespace std;

vector<vector<int>> adj;
set<int> ans;
bool visited[101];

bool dfs(int origin, int start) {
	visited[start] = true;

	int to = adj[start][0];
	if (to == origin) {
		ans.insert(start);
		return true;
	}

	if (!visited[to]) {
		if (dfs(origin, to)) {
			ans.insert(start);
			return true;
		}
	}
	return false;
}

int main() {
	int n;
	cin >> n;
	adj.resize(n + 1);

	int m;
	for (int i = 1; i <= n; i++) {
		cin >> m;
		adj[i].push_back(m);
	}

	for (int i = 1; i <= n; i++) {
		dfs(i, i);
		memset(visited, 0, sizeof(visited));
	}

	cout << ans.size() << endl;
	for (int i : ans) cout << i << endl;
	return 0;
}
