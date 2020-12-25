#include <iostream>
#include <cstring>
#include <algorithm>
#define RED 0
#define GREEN 1
#define BLUE 2
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
int cost[1000][3];
int dp[1000][3];

int dfs(int houseIdx, int colorIdx) {
	if (houseIdx == n - 1) return cost[houseIdx][colorIdx];
	int& ret = dp[houseIdx][colorIdx];
	if (ret != -1) return ret;

	int result = INF;
	if (colorIdx == RED) {
		result = min(result, dfs(houseIdx + 1, GREEN) + cost[houseIdx][colorIdx]);
		result = min(result, dfs(houseIdx + 1, BLUE) + cost[houseIdx][colorIdx]);
	}
	else if (colorIdx == GREEN) {
		result = min(result, dfs(houseIdx + 1, RED) + cost[houseIdx][colorIdx]);
		result = min(result, dfs(houseIdx + 1, BLUE) + cost[houseIdx][colorIdx]);
	}
	else if (colorIdx == BLUE) {
		result = min(result, dfs(houseIdx + 1, RED) + cost[houseIdx][colorIdx]);
		result = min(result, dfs(houseIdx + 1, GREEN) + cost[houseIdx][colorIdx]);
	}

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	}

	memset(dp, -1, sizeof(dp));

	int answer = INF;
	for (int i = 0; i < 3; i++) {
		answer = min(answer, dfs(0, i));
	}

	cout << answer;

	return 0;
}
