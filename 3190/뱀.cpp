#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
// → ↓ ← ↑
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int snake(vector<pair<pair<int, int>, bool>>& apple, char dir[]) {
	// 1. 몸길이를 늘린다 => push
	// 2. 사과를 먹는다 => continue
	// 3. 사과가 없다면 => pop
	vector<pair<int, int>> q;
	pair<int, int> nowLoc {1, 1};
	q.push_back(nowLoc);

	int timer = 0;
	int back = 0;
	int dirType = 0;
	while (1) {
		nowLoc.first += dy[dirType];
		nowLoc.second += dx[dirType];
		++timer;

		// 자기자신과 충돌하는가?
		bool crashed = find(q.begin() + back, q.end(), nowLoc) != q.end();
		// 혹은 벽과 충돌하는가?
		if (crashed || nowLoc.first > n || nowLoc.first < 1 || nowLoc.second > n || nowLoc.second < 1) break;
		
		// 사과가 있는 위치인가?
		auto it = find(apple.begin(), apple.end(), make_pair(nowLoc, false));
		// 사과를 못 먹었다면
		if (it == apple.end()) ++back;
		else (*it).second = true;

		q.push_back(nowLoc);

		// 방향 전환이 있는가?
		if (dir[timer] == 'L') {
			dirType = ((dirType - 1) + 4) % 4;
		}
		else if (dir[timer] == 'D') {
			++dirType %= 4;
		}
	}

	return timer;
}

int main() {
	cin >> n >> k;

	vector<pair<pair<int, int>, bool>> apple(k + 1);
	for (int i = 0; i < k; i++) {
		cin >> apple[i].first.first >> apple[i].first.second;
		apple[i].second = false;
	}

	int l;
	cin >> l;

	char dir[10001] {};
	for (int i = 0; i < l; i++) {
		int x; char c;
		cin >> x >> c;
		dir[x] = c;
	}

	cout << snake(apple, dir);
	return 0;
}
