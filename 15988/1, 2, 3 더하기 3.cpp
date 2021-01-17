#include <iostream>
#define MOD 1000000009
#define endl '\n'
using namespace std;

long dp[1000001];

long dfs(int n) {
	if (!n) return 1;
	long& ret = dp[n];
	if (ret) return ret;

	long result = 0;
	result = (result + dfs(n - 1) % MOD) % MOD;
	if (n >= 2) result = (result + dfs(n - 2) % MOD) % MOD;
	if (n >= 3) result = (result + dfs(n - 3) % MOD) % MOD;

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
		cout << dfs(n) << endl;
	}

	return 0;
}
