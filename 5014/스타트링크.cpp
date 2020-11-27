#include <iostream>
#include <queue>
#include <algorithm>
#define INF 987654321
using namespace std;

int main() {
	int f, s, g, u, d;
	cin >> f >> s >> g >> u >> d;

	queue<pair<int, int>> q;
	bool visited[1000001] {};

	q.push({s, 0});
	visited[s] = true;

	int minPush = INF;
	while (!q.empty()) {
		auto front = q.front();
		q.pop();
		if (front.first == g) {
			minPush = min(minPush, front.second);
			continue;
		}

		if (front.first + u <= f && !visited[front.first + u]) {
			q.push({front.first + u, front.second + 1});
			visited[front.first + u] = true;
		}
		if (front.first - d > 0 && !visited[front.first - d]) {
			q.push({front.first - d, front.second + 1});
			visited[front.first - d] = true;
		}
	}

	if (minPush == INF) cout << "use the stairs";
	else cout << minPush;
	return 0;
}
