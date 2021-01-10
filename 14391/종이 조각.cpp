#include <iostream>
#include <algorithm>
using namespace std;

int dx[] = {1, 0};
int dy[] = {0, 1};
// int dx[] = {-1, 1, 0, 0};
// int dy[] = {0, 0, -1, 1};

int n, m;
int board[4][4];
bool visited[4][4];
int answer = 0;

void dfs(int y, int x, int sum) {
	// base case: 종이를 넘어가면
	if (x >= m) {
		if (y == n - 1) {
			answer = max(answer, sum);
			return;
		}
		dfs(y + 1, 0, sum);
		return;
	}
	// base case: 이미 잘라진 곳이라면
	if (visited[y][x]) {
		dfs(y, x + 1, sum);
		return;
	}

	// 방향 선택
	for (int d = 0; d < 2; d++) {
		// 조각 개수 선택
		int lastIdx = 0;
		int tempSum = 0;
		for (int i = 0; i < 4; i++) {
			int nx = x + i * dx[d];
			int ny = y + i * dy[d];
			if (ny < 0 || ny >= n || nx < 0 || nx >= m || visited[ny][nx]) break;
			visited[ny][nx] = true;
			tempSum = tempSum * 10 + board[ny][nx];
			lastIdx = i;
			// 다음 칸으로 이동
			dfs(y, x + 1, sum + tempSum);
		}
		// 자르기 전으로 돌아간다.
		for (int i = 0; i <= lastIdx; i++) {
			int nx = x + i * dx[d];
			int ny = y + i * dy[d];
			visited[ny][nx] = false;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	char c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> c;
			board[i][j] = c - '0';
		}
	}

	dfs(0, 0, 0);
	
	cout << answer;

	return 0;
}
