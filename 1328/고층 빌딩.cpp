#include <iostream>
using namespace std;

typedef long long LL;
const LL MOD = 1e9 + 7;

LL dp[101][101][101];
LL dpLeft[101][101];
LL dpRight[101][101];

int main() {
	int n, l, r;
	cin >> n >> l >> r;

	// nCr 사전작업
	LL comb[101][101];
	for (int i = 0; i <= n; i++){
		for (int j = 0; j <= n; j++){
			if(i == j || !j) comb[i][j] = 1;
			else comb[i][j] = comb[i - 1][j - 1] % MOD + comb[i - 1][j] % MOD;
		}
	}

	// dp 테이블 초기화
	dp[1][1][1] = dp[2][2][1] = dp[2][1][2] = 1;
	dpLeft[1][1] = dpRight[1][1] = 1;
	dpLeft[2][2] = dpRight[2][1] = dpLeft[2][1] = dpRight[2][2] = 1;

	for (int i = 3; i <= n; i++) {
		for (int pos = 0; pos < i; pos++) {
			for (int left = 0; left <= pos; left++) {
				for (int right = 0; right <= i - pos - 1; right++) {
					if (!left && !right) continue;

					LL leftCase = dpLeft[pos][left];
					LL rightCase = dpRight[i - pos - 1][right];

					if (!pos) {
						dp[i][left + 1][right + 1] = (dp[i][left + 1][right + 1] + rightCase) % MOD;
						dpLeft[i][left + 1] = (dpLeft[i][left + 1] + rightCase) % MOD;
						dpRight[i][right + 1] = (dpRight[i][right + 1] + rightCase) % MOD;
					}
					else if (pos == i - 1) {
						dp[i][left + 1][right + 1] = (dp[i][left + 1][right + 1] + leftCase) % MOD;
						dpLeft[i][left + 1] = (dpLeft[i][left + 1] + leftCase) % MOD;
						dpRight[i][right + 1] = (dpRight[i][right + 1] + leftCase) % MOD;
					}
					else {
						LL allCase = (((leftCase * rightCase) % MOD) * comb[i - 1][pos]) % MOD;
						dp[i][left + 1][right + 1] = (dp[i][left + 1][right + 1] + allCase) % MOD;
						dpLeft[i][left + 1] = (dpLeft[i][left + 1] + allCase) % MOD;
						dpRight[i][right + 1] = (dpRight[i][right + 1] + allCase) % MOD;
					}
				}
			}
		}
	}

	cout << dp[n][l][r];

	return 0;
}
