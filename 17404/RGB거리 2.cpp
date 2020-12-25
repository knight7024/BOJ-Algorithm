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
int dp[3][1000][3];

int dfs(int firstColor, int houseIdx, int colorIdx) {
	if (houseIdx == n - 1) return colorIdx != firstColor ? cost[houseIdx][colorIdx] : INF;
	int& ret = dp[firstColor][houseIdx][colorIdx];
	if (ret != INF) return ret;

	int result = INF;
	if (colorIdx == RED) {
		result = min(result, dfs(firstColor, houseIdx + 1, GREEN) + cost[houseIdx][colorIdx]);
		result = min(result, dfs(firstColor, houseIdx + 1, BLUE) + cost[houseIdx][colorIdx]);
	}
	else if (colorIdx == GREEN) {
		result = min(result, dfs(firstColor, houseIdx + 1, RED) + cost[houseIdx][colorIdx]);
		result = min(result, dfs(firstColor, houseIdx + 1, BLUE) + cost[houseIdx][colorIdx]);
	}
	else if (colorIdx == BLUE) {
		result = min(result, dfs(firstColor, houseIdx + 1, RED) + cost[houseIdx][colorIdx]);
		result = min(result, dfs(firstColor, houseIdx + 1, GREEN) + cost[houseIdx][colorIdx]);
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

	memset(dp, INF, sizeof(dp));

	int answer = INF;
	for (int i = 0; i < 3; i++) {
		answer = min(answer, dfs(i, 0, i));
	}

	cout << answer;

	return 0;
}
