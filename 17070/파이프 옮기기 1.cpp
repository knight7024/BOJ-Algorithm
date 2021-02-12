#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n;
bool house[17][17];
int dp[17][17][3];

bool isInside(int ny, int nx) {
	return ny < n && ny >= 0 && nx < n && nx >= 0;
}

// 0: 가로, 1: 세로, 2: 대각선
int dfs(int y, int x, int type) {
	if (y == n - 1 && x == n - 1) return 1;
	int& ret = dp[y][x][type];
	if (ret != -1) return ret;

	ret = 0;
	// 파이프가 가로로 놓여져있다면
	int ny = y, nx = x;
	if (type == 0) {
		// 가로
		ny = y;
		nx = x + 1;
		if (isInside(ny, nx) && !house[ny][nx]) {
			ret += dfs(ny, nx, 0);
		}
		// 대각선 
		ny = y + 1;
		nx = x + 1;
		if (isInside(ny, nx) && !house[ny][nx] && isInside(y, x + 1) && !house[y][x + 1] && isInside(y + 1, x) && !house[y + 1][x]) {
			ret += dfs(ny, nx, 2);
		}
	}
	// 파이프가 세로로 놓여져있다면
	else if (type == 1) {
		// 세로
		ny = y + 1;
		nx = x;
		if (isInside(ny, nx) && !house[ny][nx]) {
			ret += dfs(ny, nx, 1);
		}
		// 대각선 
		ny = y + 1;
		nx = x + 1;
		if (isInside(ny, nx) && !house[ny][nx] && isInside(y, x + 1) && !house[y][x + 1] && isInside(y + 1, x) && !house[y + 1][x]) {
			ret += dfs(ny, nx, 2);
		}	
	}
	// 파이프가 대각선으로 놓여져있다면
	else if (type == 2) {
		// 가로
		ny = y;
		nx = x + 1;
		if (isInside(ny, nx) && !house[ny][nx]) {
			ret += dfs(ny, nx, 0);
		}
		// 세로
		ny = y + 1;
		nx = x;
		if (isInside(ny, nx) && !house[ny][nx]) {
			ret += dfs(ny, nx, 1);
		}
		// 대각선 
		ny = y + 1;
		nx = x + 1;
		if (isInside(ny, nx) && !house[ny][nx] && isInside(y, x + 1) && !house[y][x + 1] && isInside(y + 1, x) && !house[y + 1][x]) {
			ret += dfs(ny, nx, 2);
		}	
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> house[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));

	cout << dfs(0, 1, 0);

	return 0;
}
