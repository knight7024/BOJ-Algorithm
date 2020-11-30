#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int map[9][9];
vector<pair<int, int>> virus;
int maxArea;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
bool visited[9][9];

void bfs() {
	queue<pair<int, int>> q;
	for (auto v : virus) {
		q.push({v.first, v.second});
		visited[v.first][v.second] = true;
	}

	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = front.second + dx[i];
			int ny = front.first + dy[i];

			if (nx < m && nx >= 0 && ny < n && ny >= 0) {
				if (visited[ny][nx] || map[ny][nx]) continue;
				visited[ny][nx] = true;
				map[ny][nx] = 2;
				q.push({ny, nx});
			}
		}
	}
}

void backtracking(int limit, int r, int c) {
	// 벽을 다 세웠다면 bfs로 바이러스 확산시킴
	if (!limit) {
		memset(visited, 0, sizeof(visited));

		int tempMap[9][9];
		copy(&map[0][0], &map[n][m], &tempMap[0][0]);

		bfs();

		int safeArea = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				safeArea += map[i][j] == 0;
			}
		}
		maxArea = max(maxArea, safeArea);

		copy(&tempMap[0][0], &tempMap[n][m], &map[0][0]);
		return;
	}

	if (r >= n) return;
	if (c >= m) {
		backtracking(limit, r + 1, 0);
		return;
	}

	if (!map[r][c]) {
		map[r][c] = 1;
		backtracking(limit - 1, r, c + 1);
		map[r][c] = 0;
	}
	backtracking(limit, r, c + 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) virus.push_back({i, j});
		}
	}

	backtracking(3, 0, 0);

	cout << maxArea;
	return 0;
}
