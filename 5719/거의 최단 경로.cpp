#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

const int INF = 0x3f3f3f3f;

struct Node {
	int nextNode;
	int dist;
};

int n, m, s, d;
int minDist[501];
vector<vector<Node>> adj;
vector<vector<Node>> adjReverse;
bool graph[501][501];
int finalDist;
bool visited[501][501];

int dijkstra(int start, int end) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	memset(minDist, INF, sizeof(minDist));
	pq.push({0, start});
	minDist[start] = 0;

	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		int nowDist = front.first;
		int nowNode = front.second;
		if (nowDist > minDist[nowNode]) continue;

		for (auto& v : adj[nowNode]) {
			int nextNode = v.nextNode;
			int nextDist = v.dist + nowDist;
			if (!graph[nowNode][nextNode]) continue;

			if (minDist[nextNode] > nextDist) {
				minDist[nextNode] = nextDist;
				pq.push({nextDist, nextNode});
			}
		}
	}

	return minDist[end];
}

void bfs() {
	// now, previous, cost
	queue<tuple<int, int, int>> q;
	q.push({d + 1, d + 1, finalDist});

	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		int previousNode = get<1>(front);
		int nowNode = get<0>(front);
		int nowDist = get<2>(front);
		if (nowNode != previousNode) {
			graph[nowNode][previousNode] = false;
		}
		if (nowNode == s + 1) continue;

		for (auto& v : adjReverse[nowNode]) {
			if (visited[nowNode][v.nextNode] || nowDist - v.dist != minDist[v.nextNode]) continue;
			q.push({v.nextNode, nowNode, nowDist - v.dist});
			visited[nowNode][v.nextNode] = true;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (1) {
		// 장소의 수와 도로의 수
		cin >> n >> m;
		if (n == 0 && m == 0) break;

		// 시작점과 도착점
		cin >> s >> d;

		// 장소는 zero based지만 one based로 임의로 변경한다.
		adj.clear(); adj.resize(n + 1);
		adjReverse.clear(); adjReverse.resize(n + 1);
		for (int i = 0; i < m; i++) {
			int u, v, p;
			cin >> u >> v >> p;
			adj[u + 1].push_back({v + 1, p});
			adjReverse[v + 1].push_back({u + 1, p});
			graph[u + 1][v + 1] = true;
		}

		finalDist = dijkstra(s + 1, d + 1);

		memset(visited, 0, sizeof(visited));
		bfs();

		finalDist = dijkstra(s + 1, d + 1);
		cout << (finalDist == INF ? -1 : finalDist) << endl;
	}
	return 0;
}
