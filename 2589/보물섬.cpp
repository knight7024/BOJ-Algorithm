#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

struct Coor {
	int y, x;
};

int r, c;
char map[51][51];
bool visited[51][51];

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};

int bfs(int nowR, int nowC) {
	queue<pair<Coor, int>> q;
	q.push({{nowR, nowC}, 0});
	visited[nowR][nowC] = true;

	int maxDis = 0;
	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		maxDis = max(maxDis, front.second);
		for (int i = 0; i < 4; i++) {
			int nx = dx[i] + front.first.x;
			int ny = dy[i] + front.first.y;

			if (ny >= 0 && ny < r && nx >= 0 && nx < c) {
				if (map[ny][nx] == 'W' || visited[ny][nx]) continue;
				q.push({{ny, nx}, front.second + 1});
				visited[ny][nx] = true;
			}
		}
	}

	return maxDis;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
		}
	}

	int maxDis = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] == 'L') {
				maxDis = max(maxDis, bfs(i, j));
				memset(visited, 0, sizeof(visited));
			}
		}
	}

	cout << maxDis;
}
