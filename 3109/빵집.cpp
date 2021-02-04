#include <iostream>
#include <algorithm>
using namespace std;

// ↖ ← ↙
int dx[] = {-1, -1, -1};
int dy[] = {-1, 0, 1};

int r, c;
bool map[10000][500];
bool visited[10000][500];

bool dfs(int y, int x) {
	visited[y][x] = true;
	// 파이프를 연결해서 근처 빵집까지 왔다면
	if (!x) return true;

	bool result = false;
	for (int i = 0; i < 3; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || nx >= c || ny < 0 || ny >= r) continue;
		if (visited[ny][nx] || !map[ny][nx]) continue;
		result |= dfs(ny, nx);
		if (result) break;
	}

	return result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char c;
			cin >> c;
			map[i][j] = c == '.';
		}
	}

	int answer = 0;
	for (int i = 0; i < r; i++) {
		answer += dfs(i, c - 1);
	}

	cout << answer;

	return 0;
}
