#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, k, x;
	cin >> n >> m >> k >> x;

	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
	}

	queue<pair<int, int>> bfs;
	bool visited[300001] {};
	
	bfs.emplace(x, 0);
	visited[x] = true;

	vector<int> answer;
	while (!bfs.empty()) {
		auto front = bfs.front();
		bfs.pop();

		if (front.second == k) {
			answer.push_back(front.first);
			continue;
		}

		for (int i : adj[front.first]) {
			if (visited[i]) continue;
			bfs.emplace(i, front.second + 1);
			visited[i] = true;
		}
	}

	if (answer.empty()) {
		cout << -1;
		return 0;
	}

	sort(answer.begin(), answer.end());

	for (int i : answer) cout << i << ' ';

	return 0;
}
