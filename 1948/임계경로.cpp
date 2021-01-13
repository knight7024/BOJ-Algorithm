#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> adj;
int from, to;
int dist[10001];
bool visited[10001][10001];
int answer;

bool dfs(int start, int nowDist) {
	// 도착 도시에 도달했을 경우 true 반환
	if (start == to) return true;

	bool result = false;
	for (auto& i : adj[start]) {
		int nextNode = i.second;
		int nextDist = i.first + nowDist;
		// 이미 가본 적이 있다 == 최장 거리가 맞음
		// 단, 중복된 도로의 개수를 세지 않기 위해 바로 반환
		if (visited[start][nextNode]) return true;
		// 최장 거리가 아닌 경로들은 가지치기
		if (nextDist != dist[nextNode]) continue;
		visited[start][nextNode] = true;
		answer++;
		bool tempResult = dfs(nextNode, nextDist);
		// 탐색 결과가 false면 최장 거리 역추적에 실패했다는 의미
		// 방문 기록을 없앤다.
		if (!tempResult) answer--;
		visited[start][nextNode] = tempResult;
		result |= tempResult;
	}

	return result;
}

void dijkstra(int start) {
	priority_queue<pii> pq;
	pq.emplace(0, start);
	dist[start] = 0;

	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		int nowNode = front.second;
		int nowDist = front.first;
		if (nowDist < dist[nowNode]) continue;

		for (auto& i : adj[nowNode]) {
			int nextNode = i.second;
			int nextDist = i.first + nowDist;
			if (dist[nextNode] < nextDist) {
				dist[nextNode] = nextDist;
				pq.emplace(nextDist, nextNode);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	adj.resize(n + 1);
	for (int i = 0; i < m; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		adj[from].emplace_back(cost, to);
	}

	cin >> from >> to;

	memset(dist, -1, sizeof(dist));

	// 1. 최장거리로 변환한 다익스트라 수행
	dijkstra(from);
	// 2. 최장거리 역추적해서 도로의 개수 센다.
	dfs(from, 0);

	cout << *max_element(&dist[1], dist + n + 1) << ' ' << answer;

	return 0;
}
