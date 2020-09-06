#include <iostream>
#include <queue>
#define INF 987654321

using namespace std;

int main() {
	long a, b;
	cin >> a >> b;

	queue<pair<long, int>> q;
	q.push({a, 0});

	// 2를 곱하면 짝수가 되지만 1을 오른쪽에 추가하는 것은 홀수가 되므로
	// 방문했는지 여부를 확인할 필요가 없다.
	int minDist = INF;
	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		if (front.first == b)
			minDist = min(minDist, front.second);

		// 2를 곱한다.
		pair<long, int> mTwo = {front.first * 2, front.second + 1};
		if (mTwo.first <= b) q.push(mTwo);

		// 1을 오른쪽에 추가한다.
		pair<long, int> addOne = {front.first * 10 + 1, front.second + 1};
		if (addOne.first <= b) q.push(addOne);
	}
	cout << (minDist == INF ? -1 : minDist + 1);
	return 0;
}
