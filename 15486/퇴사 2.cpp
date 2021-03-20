#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	int t[1500001], p[1500001];
	for (int i = 1; i <= n; i++) {
		cin >> t[i] >> p[i];
	}

	int answer = 0;
	int dp[1500002][2] {};
	for (int i = n; i > 0; i--) {
		if (i + t[i] - 1 <= n) {
			// 상담을 하는 경우,
			dp[i][1] = max(dp[i + t[i]][0], dp[i + t[i]][1]) + p[i];
		}
		// 상담을 안 하는 경우,
		dp[i][0] = answer;
		answer = max(dp[i][0], dp[i][1]);
	}

	cout << answer;

    return 0;
}
