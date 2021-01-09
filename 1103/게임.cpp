#include <iostream>
#include <algorithm>
#define MAX 987654321
using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int n, m;
char board[50][50];
bool visited[50][50];
int dp[50][50];

int dfs(int r, int c) {
	if ((r >= n || r < 0 || c < 0 || c >= m) || board[r][c] == 'H') return 0;
	if (visited[r][c]) return MAX;
	int& ret = dp[r][c];
	if (ret) return ret;

	int result = 0;
	int step = board[r][c] - '0';
	visited[r][c] = true;
	for (int i = 0; i < 4; i++) {
		int nx = dx[i] * step + c;
		int ny = dy[i] * step + r;
		result = max(result, dfs(ny, nx) + 1);
	}
	visited[r][c] = false;

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}

	int result = dfs(0, 0);
	cout << (result >= MAX ? -1 : result);

	return 0;
}
