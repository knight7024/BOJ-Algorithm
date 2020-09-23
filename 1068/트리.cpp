#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
bool visited[51];
int ans;

void dfs(int start, bool remove) {
	bool flag = visited[start];
	visited[start] = true;

	for (int node : adj[start]) {
		if (!visited[node]) {
			flag = true;
			dfs(node, remove);
		}
	}
	if (!flag && !remove) ans++;
}

int main() {
	int n;
	cin >> n;

	vector<int> rootTree(n + 1);
	adj.resize(n + 1);

	int node, root;
	for (int i = 0; i < n; i++) {
		cin >> node;
		if (node == -1) {
			root = i;
			continue;
		}
		adj[node].push_back(i);
	}

	int rmNode;
	cin >> rmNode;
	dfs(rmNode, true);

	dfs(root, false);
	cout << ans;
	return 0;
}
