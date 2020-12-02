#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f;

void dijkstra(int start, vector<vector<pair<int, int>>>& adj, int minDist[]) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({0, start});
	minDist[start] = 0;

	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		int nowNode = front.second;
		int nowDist = front.first;
		if (minDist[nowNode] < nowDist) continue;

		for (auto& v : adj[nowNode]) {
			int nextNode = v.first;
			int nextDist = v.second + nowDist;
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

	int v, m;
	cin >> v >> m;

	vector<vector<pair<int, int>>> adj(v + 1);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}

	int j, s;
	cin >> j >> s;

	int jDist[101];
	memset(jDist, INF, sizeof(jDist));
	int sDist[101];
	memset(sDist, INF, sizeof(sDist));

	dijkstra(j, adj, jDist);
	dijkstra(s, adj, sDist);

	int minSum = INF;
	for (int i = 1; i <= v; i++) {
		if (i == j || i == s) continue;
		minSum = min(minSum, jDist[i] + sDist[i]);
	}

	int resultNode = -1;
    int minJ = INF;
    // 1. 지헌이와 성하의 출발지 제외
    // 2. 합의 최소 구하기
    // 3. 지헌이가 더 빨리 도착해야 하거나 동시에 도착해야 함
	for (int i = 1; i <= v; i++) {
		if (i == j || i == s || jDist[i] + sDist[i] != minSum || jDist[i] > sDist[i]) continue;
        if (minJ > jDist[i]) {
            resultNode = i;
            minJ = jDist[i];
        }
	}

	cout << resultNode;
	return 0;
}
