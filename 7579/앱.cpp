#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

int n, m;
vector<int> memory;
vector<int> cost;
int dp[101][100001];

int dfs(int idx, int remainCost) {
	if (idx >= n) return 0;
	int& ret = dp[idx][remainCost];
	if (ret != -1) return ret;

	ret = 0;
	if (cost[idx] <= remainCost) {
		ret = max(ret, dfs(idx + 1, remainCost - cost[idx]) + memory[idx]);
	}
	ret = max(ret, dfs(idx + 1, remainCost));

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;

	memory.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> memory[i];
	}

	int sumCost = 0;
	cost.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> cost[i];
		sumCost += cost[i];
	}

	memset(dp, -1, sizeof(dp));

	int answer = INF;
	int start = 0, end = sumCost;
	while (start <= end) {
		int mid = (start + end) / 2;
		int memoryNeeded = dfs(0, mid);
		if (memoryNeeded < m) start = mid + 1;
		else {
			answer = min(answer, mid);
			end = mid - 1;
		}
	}

	cout << answer;

	return 0;
}
