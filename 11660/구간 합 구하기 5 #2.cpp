#include <iostream>
#define endl '\n'
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	int cell[1025][1025] {};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> cell[i][j];
		}
	}

	// Pre-Processing
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cell[i][j] += cell[i - 1][j] + cell[i][j - 1] - cell[i - 1][j - 1];
		}
	}

	for (int i = 0; i < m; i++) {
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		cout << cell[y2][x2] - (cell[y1 - 1][x2] + cell[y2][x1 - 1] - cell[y1 - 1][x1 - 1]) << endl;
	}
	
	return 0;
}
