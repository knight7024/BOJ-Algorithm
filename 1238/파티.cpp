#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define endl '\n'
using namespace std;

typedef pair<int, int> PAIRII;
const int INF = 0x3f3f3f3f;

int n, m, x;
int minDist[1001];

void dijkstra(int start, vector<vector<PAIRII>>& adj, int minDist[]) {
	priority_queue<PAIRII, vector<PAIRII>, greater<>> pq;
	memset(minDist, INF, sizeof(minDist[0]) * (n + 1));
	minDist[start] = 0;
	pq.push({0, start});

	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		int nowNode = front.second;
		int nowDist = front.first;
		if (nowDist > minDist[nowNode]) continue;

		for (auto d : adj[nowNode]) {
			int nextNode = d.first;
			int nextDist = d.second + nowDist;

			if (minDist[nextNode] > nextDist) {
				minDist[nextNode] = nextDist;
				pq.push({nextDist, nextNode});
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> x;

	vector<vector<PAIRII>> adj(n + 1);
	vector<vector<PAIRII>> adjReverse(n + 1);
	for (int i = 0; i < m; i++) {
		int a, b, t;
		cin >> a >> b >> t;
		adj[a].emplace_back(b, t);
		adjReverse[b].emplace_back(a, t);
	}

	int xDist[1001];
	dijkstra(x, adj, xDist);
	
	int rDist[1001];
	dijkstra(x, adjReverse, rDist);

	int answer = 0;
	for (int i = 1; i <= n; i++) {
		if (i == x) continue;
		answer = max(answer, xDist[i] + rDist[i]);
	}

	cout << answer;
	return 0;
}
