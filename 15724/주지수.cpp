#include <iostream>
#define endl '\n'
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;

	int ground[1025][1025];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> ground[i][j];
			ground[i][j] += ground[i - 1][j] + ground[i][j - 1] - ground[i - 1][j - 1];
		}
	}

	int k;
	cin >> k;

	while (k--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cout << ground[x2][y2] - (ground[x1 - 1][y2] + ground[x2][y1 - 1] - ground[x1 - 1][y1 - 1]) << endl;
	}
  
	return 0;
}
