#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define endl '\n'
using namespace std;

int n;
vector<pair<int, int>> coins;
int dp[101][50001];

int dfs(int idx, int sum) {
	if (!sum) return 1;
	if (idx >= n || sum < 0) return 0;
	int& ret = dp[idx][sum];
	if (ret != -1) return ret;

	for (int i = 0; i <= coins[idx].second; i++) {
		ret = max(ret, dfs(idx + 1, sum - i * coins[idx].first));
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	// 3개의 입력
	for (int t = 0; t < 3; t++) {
		cin >> n;

		int target = 0;
		coins.clear();
		for (int i = 0; i < n; i++) {
			int a, b;
			cin >> a >> b;
			coins.emplace_back(a, b);
			target += a * b;
		}

		memset(dp, -1, sizeof(dp));

		if (target % 2) cout << 0 << endl;
		else cout << dfs(0, target >> 1) << endl;
	}

    return 0;
}
