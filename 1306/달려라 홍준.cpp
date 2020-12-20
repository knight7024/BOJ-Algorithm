#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	int adBoard[1000000];
	for (int i = 0; i < n; i++) {
		cin >> adBoard[i];
	}

	priority_queue<pair<int, int>> pq;
	// 전처리: 처음 M + 1칸까지 우선순위 큐에 넣는다.
	for (int i = 0; i < 2 * m - 1; i++) {
		pq.emplace(adBoard[i], i);
	}

	pair<int, int> maxBright = pq.top();
	// 처음 위치했을 때 최대 빛의 세기 출력
	cout << maxBright.first << ' ';

	// 한 칸씩 이동하면서 최대 빛의 세기 출력
	for (int i = 2 * m - 1; i < n; i++) {
		pq.emplace(adBoard[i], i);
		// 이미 지나간 광고판은 매번 제거해준다.
		while (pq.top().second <= i - (2 * m - 1)) {
			pq.pop();
		}
		cout << pq.top().first << ' ';
	}

	return 0;
}
