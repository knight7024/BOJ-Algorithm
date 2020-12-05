#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define INF 987654321
using namespace std;

long dijkstra(int start, int end, vector<vector<pair<int, int>>>& adj) {
	priority_queue<pair<long, int>, vector<pair<long, int>>, greater<>> pq;
	long minDist[801];
	fill(minDist, minDist + sizeof(minDist) / sizeof(minDist[0]), INF);
	minDist[start] = 0;
	pq.emplace(0, start);

	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		int nowNode = front.second;
		long nowDist = front.first;

		for (auto d : adj[nowNode]) {
			int nextNode = d.first;
			long nextDist = d.second + nowDist;

			if (minDist[nextNode] > nextDist) {
				minDist[nextNode] = nextDist;
				pq.emplace(nextDist, nextNode);
			}
		}
	}
	return minDist[end];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, e;
	cin >> n >> e;

	vector<vector<pair<int, int>>> adj(n + 1);
	for (int i = 0; i < e; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].emplace_back(b, c);
		adj[b].emplace_back(a, c);
	}

	int v1, v2;
	cin >> v1 >> v2;

	long result = min(dijkstra(1, v1, adj) + dijkstra(v1, v2, adj) + dijkstra(v2, n, adj), dijkstra(1, v2, adj) + dijkstra(v2, v1, adj) + dijkstra(v1, n, adj));
	cout << (result >= INF ? -1 : result);
	return 0;
}
