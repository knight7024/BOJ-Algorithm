#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#define endl '\n'
using namespace std;

typedef pair<int, int> PAIRII;
const int INF = 0x3f3f3f3f;

int minDist[1001];
vector<string> result;

void dijkstra(int start, vector<vector<PAIRII>>& adj) {
	priority_queue<PAIRII, vector<PAIRII>, greater<>> pq;
	memset(minDist, INF, sizeof(minDist));
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

void bfs(int start, vector<vector<PAIRII>>& adj) {
	queue<PAIRII> q;
	q.emplace(start, 0);

	bool visited[1001] {};
	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		int nowNode = front.first;
		int nowDist = front.second;

		for (auto& v : adj[nowNode]) {
			int nextNode = v.first;
			int nextDist = nowDist + v.second;
			if (minDist[nextNode] != nextDist || visited[nextNode]) continue;
			visited[nextNode] = true;
			q.emplace(nextNode, nextDist);
			result.push_back(to_string(nowNode) + " " + to_string(nextNode));
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<PAIRII>> adj(n + 1);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].emplace_back(b, c);
		adj[b].emplace_back(a, c);
	}

	dijkstra(1, adj);
	bfs(1, adj);

	cout << result.size() << endl;
	for (auto& s : result) cout << s << endl;

	return 0;
}
