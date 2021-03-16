#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Coins {
	int y1, x1;
	int y2, x2;
	int count;
	Coins() {}
	Coins(int y1, int x1, int y2, int x2, int count): y1(y1), x1(x1), y2(y2), x2(x2), count(count) {}
};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n, m;

bool outOfBound(int y, int x) {
	return y < 0 || y >= n || x < 0 || x >= m;
}

int main() {
	cin >> n >> m;

	Coins coins {};
	bool board[20][20] {};
	// 1번 동전의 위치, 2번 동전의 위치
	bool visited[20][20][20][20] {};
	bool type = false;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			board[i][j] = (c == '.' || c == 'o');
			if (c == 'o') {
				if (!type) coins.y1 = i, coins.x1 = j;
				else coins.y2 = i, coins.x2 = j;
				type ^= 1;
			}
		}
	}

	queue<Coins> bfs;
	bfs.emplace(coins);
	visited[coins.y1][coins.x1][coins.y2][coins.x2] = true;

	while (!bfs.empty()) {
		auto front = bfs.front();
		bfs.pop();

		if (front.count >= 10) {
			cout << -1;
			exit(0);
		}

		for (int i = 0; i < 4; i++) {
			int ny1 = dy[i] + front.y1, nx1 = dx[i] + front.x1;
			int ny2 = dy[i] + front.y2, nx2 = dx[i] + front.x2;

			// 두 동전 모두 보드에서 떨어지면, 잘못된 경우
			if (outOfBound(ny1, nx1) && outOfBound(ny2, nx2)) continue;
			// 동전이 이동하려는 방향에 칸이 없으면 동전은 보드 바깥으로 떨어진다.
			if (outOfBound(ny1, nx1) || outOfBound(ny2, nx2)) {
				cout << front.count + 1;
				exit(0);
			}
			// 이미 방문했던 곳이라면
			if (visited[ny1][nx1][ny2][nx2]) continue;
			// 동전이 이동하려는 칸이 벽이면, 동전은 이동하지 않는다.
			if (!board[ny1][nx1] || !board[ny2][nx2]) {
				if (!board[ny1][nx1]) ny1 = front.y1, nx1 = front.x1;
				if (!board[ny2][nx2]) ny2 = front.y2, nx2 = front.x2;
				if (visited[ny1][nx1][ny2][nx2]) continue;
				bfs.emplace(ny1, nx1, ny2, nx2, front.count + 1);
				visited[ny1][nx1][ny2][nx2] = true;
				continue;
			}

			bfs.emplace(ny1, nx1, ny2, nx2, front.count + 1);
			visited[ny1][nx1][ny2][nx2] = true;
		}
	}

	cout << -1;

	return 0;
}
