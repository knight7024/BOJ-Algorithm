#include <iostream>
#include <cstring>
#include <algorithm>
#define endl '\n'
#define MOD 1000000007
using namespace std;

int l;
// [A][B]: A번째 괄호 문자 '('의 개수가 B일 때 괄호 문자열의 개수
int dp[5000][2500];

int dfs(int idx, int left) {
	// base case: 괄호 문자열 완성
	if (idx == l) return left == 0;
	// 가지치기
	if (left > l / 2 || l - idx < left) return 0;
	int& ret = dp[idx][left];
	if (ret != -1) return ret;

	int result = 0;
	if (left > 0) {
		result = (result % MOD + dfs(idx + 1, left - 1) % MOD) % MOD;
	}
	result = (result % MOD + dfs(idx + 1, left + 1) % MOD) % MOD;

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;

	while (t--) {
		cin >> l;

		memset(dp, -1, sizeof(dp));

		if (l % 2) {
			cout << 0 << endl;
			continue;
		}
		cout << dfs(0, 0) << endl;
	}
	return 0;
}
