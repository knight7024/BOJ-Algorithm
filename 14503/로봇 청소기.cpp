#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Coor {
	int y, x;
	int dir = -1;
	Coor() {}
	Coor(int y, int x, int dir): y(y), x(x), dir(dir) {};
};

// 북, 동, 남, 서
const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
// 다음 회전할 방향 매핑
const int rotateDir[] = {3, 0, 1, 2};

int main() {
	int n, m;
	cin >> n >> m;

	Coor now;
	cin >> now.y >> now.x >> now.dir;

	bool map[51][51];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	int answer = 0;
	bool cleaned[51][51] {};
	while (1) {
		// 현재 위치를 청소한다.
		if (!cleaned[now.y][now.x]) {
			cleaned[now.y][now.x] = true;
			answer++;
		}
		// 현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
		bool isDirty = false;
		int nowDir = now.dir;
		for (int i = 0; i < 4; i++) {
			nowDir = rotateDir[nowDir];
			int ny = now.y + dy[nowDir];
			int nx = now.x + dx[nowDir];
			// 왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전한다.
			if (ny >= n || ny < 0 || nx >= m || nx < 0 || map[ny][nx]) continue;
			if (!cleaned[ny][nx]) {
				isDirty = true;
				break;
			}
		}
		// 왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진한다.
		if (isDirty) {
			now.dir = nowDir;
			now.y += dy[now.dir];
			now.x += dx[now.dir];
		}
		// 네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진한다.
		else {
			now.y -= dy[now.dir];
			now.x -= dx[now.dir];
			// 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
			if (now.y >= n || now.y < 0 || now.x >= m || now.x < 0 || map[now.y][now.x]) break;
		}
	}

	cout << answer;

	return 0;
}
