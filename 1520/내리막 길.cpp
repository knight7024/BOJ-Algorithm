#include <iostream>
#include <cstring>

using namespace std;

int r, c;
int map[501][501];
int dp[501][501];
int dx[] = { -1, 1, 0, 0};
int dy[] = { 0, 0, -1, 1};

int dfs(int nowR, int nowC) {
	int& ret = dp[nowR][nowC];
	if (ret != -1) return ret;

	if (nowR == r - 1 && nowC == c - 1) return ret = 1;

	int dir = 0;
	for (int i = 0; i < 4; i++) {
		int nextR = nowR + dy[i];
		int nextC = nowC + dx[i];

		if (nextR >= 0 && nextR < r && nextC >= 0 && nextC < c) {
			if (map[nextR][nextC] < map[nowR][nowC]) {
				dir += dfs(nextR, nextC);
			}
		}
	}
	return ret = dir;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));

	cout << dfs(0, 0);
	return 0;
}
