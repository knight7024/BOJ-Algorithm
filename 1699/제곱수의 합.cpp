#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	int dp[100001];
	for (int i = 1; i * i <= n; i++) {
		int t = i * i;
		for (int j = t; j <= n; j++) {
			if (i == 1) dp[j] = j;
			else if (j % t == 0) dp[j] = j / t;
			else if (j > t) dp[j] = min(dp[j], dp[j / t * t] + dp[j % t]);
		}
	}
	cout << dp[n];
	return 0;
}
