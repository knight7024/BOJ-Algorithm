#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Coor {
	int y, x;
	Coor() {}
	Coor(int y, int x): y(y), x(x) {}
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;

	int allCount = 0;
	bool board[101][101];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			allCount += board[i][j];
		}
	}

	queue<Coor> bfs;
	int count[101][101];
	bool visited[101][101];
	int answer = 0;
	while (allCount) {
		bfs.emplace(0, 0);
		memset(count, 0, sizeof(count));
		memset(visited, 0, sizeof(visited));
		answer++;
		while (!bfs.empty()) {
			auto front = bfs.front();
			bfs.pop();

			for (int i = 0; i < 4; i++) {
				int ny = front.y + dy[i];
				int nx = front.x + dx[i];

				if (nx >= m || nx < 0 || ny >= n || ny < 0) continue;
				if (visited[ny][nx]) continue;

				if (board[ny][nx] && ++count[ny][nx] >= 2) {
					board[ny][nx] = 0;
					visited[ny][nx] = true;
					allCount--;
					continue;
				}

				if (!board[ny][nx]) {
					bfs.emplace(ny, nx);
					visited[ny][nx] = true;
				}
			}
		}
	}

	cout << answer;

	return 0;
}
