#include <iostream>
#include <algorithm>
using namespace std;

const int MIN = -987654321;

int dx[] = {-1, 1, 0};
int dy[] = {0, 0, 1};

int n, m;
int mars[1000][1000];
int dp[3][1000][1000];

int dfs(int prev, int y, int x) {
	if (y == n - 1 && x == m - 1) return mars[y][x];
	int& ret = dp[prev][y][x];
	if (ret != MIN) return ret;

	for (int i = 0; i < 3; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
		// ←로 갔다가 →로 가는 것, 혹은 →로 갔다가 ←로 가는 것 방지
		if ((prev == 0 && i == 1) || (prev == 1 && i == 0)) continue;
		ret = max(ret, dfs(i, ny, nx) + mars[y][x]);
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> mars[i][j];
			dp[0][i][j] = dp[1][i][j] = dp[2][i][j] = MIN;
		}
	}

	cout << dfs(2, 0, 0);

	return 0;
}
