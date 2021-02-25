#include <iostream>
#include <queue>
using namespace std;

struct Coor {
	int y, x;
	int jump;
	int count;
	Coor() {}
	Coor(int y, int x): y(y), x(x) {}
	Coor(int y, int x, int jump): y(y), x(x), jump(jump) {}
	Coor(int y, int x, int jump, int count): y(y), x(x), jump(jump), count(count) {}
};

int dxNormal[] = {-1, 1, 0, 0};
int dyNormal[] = {0, 0, -1, 1};
int dxHorse[] = {-1, -2, 1, 2, -1, -2, 1, 2};
int dyHorse[] = {-2, -1, -2, -1, 2, 1, 2, 1};

int main() {
	int k;
	cin >> k;

	int w, h;
	cin >> w >> h;

	bool board[201][201];
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> board[i][j];
		}
	}

	queue<Coor> bfs;
	// (y, x) 좌표에 말처럼 움직이거나 원숭이로 움직인 상태 저장
	bool visited[201][201][31] {};
	bfs.emplace(0, 0);
	visited[0][0][0] = true;

	while (!bfs.empty()) {
		auto front = bfs.front();
		bfs.pop();

		if (front.y == h - 1 && front.x == w - 1) {
			cout << front.count;
			exit(0);
		}

		// 말처럼 움직이기
		if (front.jump < k) {
			for (int i = 0; i < 8; i++) {
				int nx = dxHorse[i] + front.x;
				int ny = dyHorse[i] + front.y;

				if (nx >= w || nx < 0 || ny >= h || ny < 0) continue;
				if (board[ny][nx]) continue;

				if (!visited[ny][nx][front.jump + 1]) {
					bfs.emplace(ny, nx, front.jump + 1, front.count + 1);
					visited[ny][nx][front.jump + 1] = true;
				}
			}
		}
		// 원숭이로 움직이기
		for (int i = 0; i < 4; i++) {
			int nx = dxNormal[i] + front.x;
			int ny = dyNormal[i] + front.y;

			if (nx >= w || nx < 0 || ny >= h || ny < 0) continue;
			if (board[ny][nx]) continue;

			if (!visited[ny][nx][front.jump]) {
				bfs.emplace(ny, nx, front.jump, front.count + 1);
				visited[ny][nx][front.jump] = true;
			}
		}
	}

	cout << -1;

	return 0;
}
