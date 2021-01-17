#include <iostream>
#define MOD 1000000009
#define endl '\n'
using namespace std;

long dp[100001][4];

long dfs(int n, int prev) {
	if (!n) return 1;
	long& ret = dp[n][prev];
	if (ret) return ret;

	long result = 0;
	if (prev != 1) result = (result + dfs(n - 1, 1) % MOD) % MOD;
	if (prev != 2 && n >= 2) result = (result + dfs(n - 2, 2) % MOD) % MOD;
	if (prev != 3 && n >= 3) result = (result + dfs(n - 3, 3) % MOD) % MOD;

	return ret = result;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--)
	{
		int n;
		cin >> n;
		cout << dfs(n, 0) << endl;
	}

	return 0;
}
