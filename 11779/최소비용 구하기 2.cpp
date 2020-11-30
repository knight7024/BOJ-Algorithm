#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define endl '\n'
using namespace std;

int minDist[1001];
int shortestDir[1001];

void dijkstra(int start, vector<vector<pair<int, int>>>& adj) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	memset(minDist, 0x3f, sizeof(minDist));
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
        // 최단 거리를 가지는 경로 기록
				shortestDir[nextNode] = nowNode;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> adj(n + 1);
	for (int i = 0; i < m; i++) {
		int city1, city2, dist;
		cin >> city1 >> city2 >> dist;
		adj[city1].push_back({city2, dist});
	}

	int depart, arrive;
	cin >> depart >> arrive;

	dijkstra(depart, adj);

	// 최소 비용
	cout << minDist[arrive] << endl;
	// 도시의 개수
	vector<int> shortestCity;
	while (arrive) {
		shortestCity.push_back(arrive);
		arrive = shortestDir[arrive];
	}
	cout << shortestCity.size() << endl;
	for (auto it = shortestCity.rbegin(); it != shortestCity.rend(); it++) {
		cout << *it << ' ';
	}
}
