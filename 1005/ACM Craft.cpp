#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--) {
		int n, k;
		cin >> n >> k;

		int cost[1001];
		for (int i = 1; i <= n; i++) {
			cin >> cost[i];
		}

		vector<vector<int>> adj(n + 1);
		int indegree[1001] {};
		for (int i = 0; i < k; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			indegree[b]++;
		}

		int w;
		cin >> w;

		queue<int> topo;
		for (int i = 1; i <= n; i++) {
			if (!indegree[i]) topo.push(i);
		}

		int minCost[1001] {};
		while (!topo.empty()) {
			int front = topo.front();
			topo.pop();
			minCost[front] += cost[front];

			for (int& i : adj[front]) {
				if (!--indegree[i]) topo.push(i);
				minCost[i] = max(minCost[i], minCost[front]);
			}
		}

		cout << minCost[w] << endl;
	}

	return 0;
}
