#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
int jobCost[20][20];
// [A][B]: A번째 일을 수행한 상태가 B일 때 최소 비용
int dp[20][1 << 20];

int dfs(int idx, int state) {
	if (!state) return 0;
	int& ret = dp[idx][state];
	if (ret != INF) return ret;

	// i번 사람이 idx번 일을 수행한다.
	for (int i = 0; i < n; i++) {
		if (!(state & 1 << i)) continue;
		ret = min(ret, dfs(idx + 1, state ^ 1 << i) + jobCost[idx][i]);
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> jobCost[i][j];
		}
	}

	memset(dp, INF, sizeof(dp));

	cout << dfs(0, (1 << n) - 1);

	return 0;
}
