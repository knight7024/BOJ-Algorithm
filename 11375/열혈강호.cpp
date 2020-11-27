#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m;
bool visited[1001];
int matched[1001];

bool bipartiteMatching(int start, vector<vector<int>>& adj) {
	for (int j : adj[start]) {
		if (visited[j]) continue;
		visited[j] = true;

		if (!matched[j] || bipartiteMatching(matched[j], adj)) {
			matched[j] = start;
			return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;

	vector<vector<int>> adj(m + 1);
	for (int i = 1; i <= n; i++) {
		int w;
		cin >> w;

		int wn;
		for (int j = 0; j < w; j++) {
			cin >> wn;

			adj[wn].push_back(i);
		}
	}

	int count = 0;
	for (int i = 1; i <= m; i++) {
		count += bipartiteMatching(i, adj);
		memset(visited, 0, sizeof(visited));
	}

	cout << count << endl;
	return 0;
}
