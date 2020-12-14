#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<pair<int, int>> coor;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		coor.emplace_back(x, 0);
	}

	for (int i = 0; i < n - 1; i++) {
		int x;
		cin >> x;
		coor[i].second = x;
	}

	if (n == 1) {
		cout << "권병장님, 중대장님이 찾으십니다";
		return 0;
	}

	int target = coor[n - 1].first;
	int maxRange = 0;
	for (int i = 0; i < n - 1; i++) {
		if (coor[i].first > maxRange) break;
		maxRange = max(maxRange, coor[i].first + coor[i].second);
		if (maxRange >= target) {
			cout << "권병장님, 중대장님이 찾으십니다";
			return 0;
		}
	}

	cout << "엄마 나 전역 늦어질 것 같아";
    return 0;
}
