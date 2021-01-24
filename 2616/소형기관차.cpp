#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n, t;
vector<int> pSum = {0};
int dp[50002][4];

int dfs(int idx, int rest) {
	if (idx > n || !rest) return 0;
	int& ret = dp[idx][rest];
	if (ret != -1) return ret;

	int result = max(0, dfs(idx + 1, rest));
	result = max(result, dfs(idx + t, rest - 1) + pSum[idx] - pSum[idx - t]);

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	vector<int> train(n);
	for (int i = 0; i < n; i++) {
		cin >> train[i];
		pSum.emplace_back(train[i] + pSum.back());
	}

	cin >> t;

	memset(dp, -1, sizeof(dp));

	cout << dfs(t - 1, 3);

	return 0;
}
