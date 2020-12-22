#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> adj(n + 1);
	int indegree[32001] {};
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].emplace_back(b);
		indegree[b]++;
	}

	priority_queue<int, vector<int>, greater<>> pq;
	for (int i = 1; i <= n; i++) {
		if (indegree[i]) continue;
		pq.push(i);
	}

	while (!pq.empty()) {
		int front = pq.top();
		cout << front << ' ';
		pq.pop();

		for (int& i : adj[front]) {
			if (--indegree[i]) continue;
			pq.push(i);
		}
	}

	return 0;
}
