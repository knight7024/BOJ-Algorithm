#include <iostream>
#include <cstring>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n, m, k;
char board[101][101];
char target[81];
int dp[101][101][80];

int dfs(int y, int x, int idx) {
	if (!target[idx]) return 1;
	int& ret = dp[y][x][idx];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= k; j++) {
			int ny = y + dy[i] * j;
			int nx = x + dx[i] * j;
			if (ny >= n || ny < 0 || nx >= m || nx < 0) continue;

			if (board[ny][nx] == target[idx]) {
				ret += dfs(ny, nx, idx + 1);
			}
		}
	}

	return ret;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}

	cin.ignore();
	cin.getline(target, sizeof(target));

	memset(dp, -1, sizeof(dp));

	int answer = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == target[0]) {
				answer += dfs(i, j, 1);
			}
		}
	}

	cout << answer;

	return 0;
}
