#include <iostream>
using namespace std;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	// → 또는 ↑ 방향으로 (x, y) 좌표로 오는 길이 막혔는지 여부
	bool stuck[2][101][101] {};
	for (int i = 0; i < k; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		stuck[a == c][max(a, c)][max(b, d)] = true;
	}

	long dp[101][101] {};
	dp[0][0] = 1;
	for (int j = 0; j <= m; j++) {
		for (int i = 0; i <= n; i++) {
			if (!i && !j) continue;
			if (!i || !j) {
				if (stuck[0][i][j] || stuck[1][i][j]) continue;
				dp[i][j] = !i ? dp[i][j - 1] : dp[i - 1][j];
			}
			else {
				if (!stuck[0][i][j]) dp[i][j] += dp[i - 1][j];
				if (!stuck[1][i][j]) dp[i][j] += dp[i][j - 1];
			}
		}
	}

	cout << dp[n][m];

	return 0;
 }
