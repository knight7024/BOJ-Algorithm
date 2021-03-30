#include <iostream>
#include <cstring>
#define endl '\n'
using namespace std;

int n;
long dp[61][31][31];

long dfs(int idx, int two, int one) {
	if (idx >= n * 2) return two == 0 && one == 0;
	long& ret = dp[idx][two][one];
	if (ret != -1) return ret;
	
	ret = 0;
	// 한 개짜리 알약이 남아있으면
	if (two) ret += dfs(idx + 1, two - 1, one + 1);
	// 반 개짜리 알약이 남아있으면
	if (one) ret += dfs(idx + 1, two, one - 1);
	
	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
    
	memset(dp , -1, sizeof(dp));
	
	while (1) {
		cin >> n;
		if (!n) break;
		cout << dfs(0, n, 0) << endl;
	}
	
	return 0;
}
