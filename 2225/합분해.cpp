#include <iostream>
#define MOD 1000000000
using namespace std;

int n, k;
long dp[201][201];

long dfs(int idx, int sum) {
	if (idx == k) return sum == n;
	long& ret = dp[idx][sum];
	if (ret) return ret;

	for (int i = 0; i <= n - sum; i++) {
		ret = (ret + dfs(idx + 1, sum + i) % MOD) % MOD;
	}

	return ret;
}

int main() {
	cin >> n >> k;

	cout << dfs(0, 0);
}
