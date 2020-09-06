#include <iostream>
#define endl '\n'

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;

	int range[1025][1025] {};
	for (int i = 1; i <= n; i++) {
		int prefixSum = 0;
		for (int j = 1; j <= n; j++) {
			cin >> range[i][j];
			prefixSum += range[i][j];
			range[i][j] = prefixSum;
		}
	}

	int x1, y1, x2, y2;
	for (int i = 0; i < m; i++) {
		cin >> y1 >> x1 >> y2 >> x2;

		int answer = 0;
		for (int y = y1; y <= y2; y++) {
			answer += range[y][x2] - range[y][x1 - 1];
		}
		cout << answer << endl;
	}
	return 0;
}
