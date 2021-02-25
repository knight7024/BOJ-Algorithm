#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x7f7f7f7f;

int n, m;
vector<int> dist;
vector<int> weather;
int dp[1001][1001];

int dfs(int node, int day) {
	if (node == n) return 0;
	int& ret = dp[node][day];
	if (ret != INF) return ret;

	if (m - day >= n - node) {
		ret = min(ret, dfs(node + 1, day + 1) + dist[node + 1] * weather[day + 1]);
		ret = min(ret, dfs(node, day + 1));
	}

	return ret;
}

int main() {
	cin >> n >> m;

	dist.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> dist[i];
	}

	weather.resize(m + 1);
	for (int i = 1; i <= m; i++) {
		cin >> weather[i];
	}

	memset(dp, INF, sizeof(dp));

	cout << dfs(0, 0);

	return 0;
}
