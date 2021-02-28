#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define endl '\n'
using namespace std;

int n;
vector<int> weight;
int dp[30][40001];

int dfs(int idx, int weightSum) {
	if (!weightSum) return 1;
	if (idx >= n || weightSum < 0) return 0;
	int& ret = dp[idx][weightSum];
	if (ret != -1) return ret;

	int result = 0;
	result = max(result, dfs(idx + 1, weightSum));
	result = max(result, dfs(idx + 1, weightSum + weight[idx]));
	result = max(result, dfs(idx + 1, abs(weightSum - weight[idx])));

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	weight.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> weight[i];
	}

	int m;
	cin >> m;

	vector<int> marble(m);
	for (int i = 0; i < m; i++) {
		cin >> marble[i];
	}

	memset(dp, -1, sizeof(dp));

	for (int i : marble) {
		cout << (dfs(0, i) ? 'Y' : 'N') << ' ';
	}

    return 0;
}
