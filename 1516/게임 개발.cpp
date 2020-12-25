#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> adj(n + 1);
	int cost[501];
	int indegree[501] {};
	for (int i = 1; i <= n; i++) {
		cin >> cost[i];
		int preBuild;
		while (1) {
			cin >> preBuild;
			if (preBuild == -1) break;
			adj[preBuild].emplace_back(i);
			indegree[i]++;
		}
	}

	queue<int> topo;
	for (int i = 1; i <= n; i++) {
		if (!indegree[i]) topo.push(i);
	}

	int minCost[501] {};
	while (!topo.empty()) {
		int front = topo.front();
		topo.pop();
		minCost[front] += cost[front];

		for (int& i : adj[front]) {
			if (!--indegree[i]) topo.push(i);
			minCost[i] = max(minCost[i], minCost[front]);
		}
	}

	for (int i = 1; i <= n; i++) {
		cout << minCost[i] << ' ';
	}

	return 0;
}
