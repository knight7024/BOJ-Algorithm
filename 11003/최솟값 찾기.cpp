#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int n, l;
	cin >> n >> l;

	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	// Sliding Window
	priority_queue<pair<int, int>> pq;
	int from = 1 - l, to = 0;
	for (int i = from; i <= to; i++) {
		if (i < 0) continue;
		pq.emplace(-arr[i], i);
	}

	while (to < n) {
		cout << -pq.top().first << ' ';
		from++; to++;
		pq.emplace(-arr[to], to);
		while (pq.top().second < from || pq.top().second > to) pq.pop();
	}

	return 0;
}
