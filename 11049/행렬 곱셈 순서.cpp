#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

vector<pair<int, int>> dim;
int dp[501][501];

int dfs(int from, int to) {
	if (from == to) return 0;
	int& ret = dp[from][to];
	if (ret != -1) return ret;

	int result = INF;
	// 분할정복 + DP
	// 행렬이 하나만 남을 때까지 배열을 잘게 쪼개고,
	// 행렬의 곱을 더하면서 올라온다.
	// 위의 과정을 N번 반복한다.
	// O(N^3)
	for (int i = from; i < to; i++) {
		result = min(result, dfs(from, i) + dfs(i + 1, to) + dim[from].first * dim[i].second * dim[to].second);
	}

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int r, c;
		cin >> r >> c;
		dim.emplace_back(r, c);
	}

	memset(dp, -1, sizeof(dp));

	cout << dfs(0, n - 1);

	return 0;
}
