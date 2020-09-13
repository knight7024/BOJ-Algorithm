#include <iostream>
#include <cstring>

using namespace std;

int n;
int map[501][501];
int dp[501][501];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int dfs(int nowR, int nowC) {
	int& ret = dp[nowR][nowC];
	if (ret != -1) return ret;

	int maxK = 1;
	for (int i = 0; i < 4; i++) {
		int nextR = nowR + dy[i];
		int nextC = nowC + dx[i];

		int k = 1;
		if (nextR >= 0 && nextR < n && nextC >= 0 && nextC < n) {
			if (map[nextR][nextC] > map[nowR][nowC]) {
				k += dfs(nextR, nextC);
				maxK = max(maxK, k);
			}
		}
	}
	return ret = max(ret, maxK);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));

	int maxK = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			maxK = max(maxK, dfs(i, j));
		}
	}
	cout << maxK;
	return 0;
}
