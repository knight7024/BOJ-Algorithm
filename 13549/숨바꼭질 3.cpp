#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define MAX 100000
#define INF 987654321

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;

	// 시간 (가중치), 위치
	priority_queue<pair<int, int>,vector<pair<int, int>>,greater<pair<int, int>>> pq;
	vector<int> minDist(2 * MAX + 1, INF);

	pq.push({0, n});
	minDist[n] = 0;

	if (n == k) cout << 0, exit(0);

	// 다익스트라 알고리즘
	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		// 이미 저장된 가중치보다 크다면 넘어간다.
		if (minDist[front.second] < front.first) continue;

		// X-1로 이동
		pair<int, int> walkBack = {1 + minDist[front.second], front.second - 1};
		if (walkBack.second >= 0) {
			if (minDist[walkBack.second] > walkBack.first) {
				minDist[walkBack.second] = walkBack.first;
				pq.push(walkBack);
			}
		}

		// X+1로 이동
		pair<int, int> walkFront = {1 + minDist[front.second], front.second + 1};
		if (walkFront.second <= 2 * k) {
			if (minDist[walkFront.second] > walkFront.first) {
				minDist[walkFront.second] = walkFront.first;
				pq.push(walkFront);
			}
		}

		// 순간이동
		pair<int, int> teleport = {minDist[front.second], front.second * 2};
		if (teleport.second <= 2 * k) {
			if (minDist[teleport.second] > teleport.first) {
				minDist[teleport.second] = teleport.first;
				pq.push(teleport);
			}
		}
	}
	cout << minDist[k];
	return 0;
}
