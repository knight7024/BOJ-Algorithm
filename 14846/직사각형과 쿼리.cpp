#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	int matrix[301][301];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> matrix[i][j];
			matrix[i][j]--;
		}
	}

	int prefixSum[301][301][10] {};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			prefixSum[i][j][matrix[i][j]]++;
			for (int k = 0; k < 10; k++) {
				prefixSum[i][j][k] += prefixSum[i - 1][j][k] + prefixSum[i][j - 1][k] - prefixSum[i - 1][j - 1][k];
			}
		}
	}

	int q;
	cin >> q;

	while (q--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		int answer = 0;
		for (int k = 0; k < 10; k++) {
			answer += prefixSum[x2][y2][k] - (prefixSum[x1 - 1][y2][k] + prefixSum[x2][y1 - 1][k] - prefixSum[x1 - 1][y1 - 1][k]) != 0;
		}
		cout << answer << endl;
	}

	return 0;
}
