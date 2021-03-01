#include <iostream>
#include <queue>
using namespace std;

struct Coor {
	int y, x;
	int dist;
	Coor() {}
	Coor(int y, int x, int dist): y(y), x(x), dist(dist) {}
};

const int INF = 0x3f3f3f3f;

int main() {
	int n, m;
	cin >> n >> m;

	queue<Coor> bfs;
	int board[50][50];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			if (board[i][j]) bfs.emplace(i, j, 1);
			else board[i][j] = INF;
		}
	}

	const int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
	const int dy[] = {0, 0, -1, 1, -1, -1, 1, 1};

	while (!bfs.empty()) {
		auto front = bfs.front();
		bfs.pop();

		for (int i = 0; i < 8; i++) {
			int nx = front.x + dx[i];
			int ny = front.y + dy[i];
			if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;

			if (board[ny][nx] > front.dist + 1) {
				board[ny][nx] = front.dist + 1;
				bfs.emplace(ny, nx, front.dist + 1);
			}
		}
	}

	int answer = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			answer = max(answer, board[i][j]);
		}
	}

	cout << answer - 1;

	return 0;
}
