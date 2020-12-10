#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<LL, int> PAIRLI;
const int INF = 0x3f3f3f3f;

int n, m;
int oilPrice[2501];
int minDist[2501][2501];

void dijkstra(int start, vector<vector<PAIRLI>>& adj) {
	priority_queue<PAIRLI, vector<PAIRLI>, greater<>> pq;
	pq.emplace(0, start);
	minDist[start][start] = 0;

	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		int nowNode = front.second;
		LL nowDist = front.first;
		if (nowDist > minDist[start][nowNode]) continue;

		for (auto& d : adj[nowNode]) {
			int nextNode = d.second;
			LL nextDist = d.first + nowDist;

			if (minDist[start][nextNode] > nextDist) {
				minDist[start][nextNode] = nextDist;
				pq.emplace(nextDist, nextNode);
			}
		}
	}
}

LL bfs(int start) {
	// BFS + DP
	// 최단 거리만큼 그래프를 탐색하고 N번까지 이동하는 최소의 비용 구한다.
	priority_queue<PAIRLI, vector<PAIRLI>, greater<>> pq;
	pq.emplace(0, start);
	
	LL minCost[2501];
	memset(minCost, INF, sizeof(minCost));
	minCost[start] = 0;

	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		int nowNode = front.second;
		LL nowCost = front.first;
		if (minCost[nowNode] < nowCost) continue;
		
		for (int i = 1; i <= n; i++) {
			if (i == nowNode || minDist[nowNode][i] == INF) continue;

			LL nextCost = nowCost + (LL) oilPrice[nowNode] * minDist[nowNode][i];
			if (minCost[i] > nextCost) {
				minCost[i] = nextCost;
				pq.emplace(nextCost, i);
			}
		}
	}

	return minCost[n];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		cin >> oilPrice[i];
	}

	vector<vector<PAIRLI>> adj(n + 1);
	for (int i = 0; i < m; i++) {
		int a, b; LL d;
		cin >> a >> b >> d;
		adj[a].emplace_back(d, b);
		adj[b].emplace_back(d, a);
	}

	memset(minDist, INF, sizeof(minDist));
	// 다익스트라를 도시 수만큼 돌려서 모든 최단 거리를 구한다.
	for (int i = 1; i <= n; i++) {
		dijkstra(i, adj);
	}

	cout << bfs(1);

	return 0;
}
