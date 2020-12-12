#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n, k;
vector<pair<int, int>> backpack;
int dp[101][100001];

int dfs(int weight, int idx) {
	if (idx == n) return 0;
	int& ret = dp[idx][weight];
	if (ret != -1) return ret;

	int nextItemWeight = backpack[idx].first;
	int nextItemHappiness = backpack[idx].second;
	int result = 0;
	if (weight + nextItemWeight <= k) {
		result = dfs(weight + nextItemWeight, idx + 1) + nextItemHappiness;
	}
	result = max(result, dfs(weight, idx + 1));

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		int w, v;
		cin >> w >> v;
		backpack.emplace_back(w, v);
	}

	memset(dp, -1, sizeof(dp));

	cout << dfs(0, 0);
	return 0;
}
