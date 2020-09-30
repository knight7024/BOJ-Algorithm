#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 987654321

using namespace std;

struct coor {
	int y;
	int x;
	int index;
	int dist;
};

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	int map[101][101];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	bool visited[101][101] {};
	queue<coor> q;
	int index = 1;

	// 다리를 연결하기에 앞서 섬들을 분리시켜줘야 한다.
	// ex) 1번 섬, 2번 섬, 3번 섬...
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] || !map[i][j]) continue;

			q.push({i, j, index});
			visited[i][j] = true;
			map[i][j] = index++;

			while (!q.empty()) {
				auto front = q.front();
				q.pop();

				for (int d = 0; d < 4; d++) {
					int nx = front.x + dx[d];
					int ny = front.y + dy[d];

					if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
						if (visited[ny][nx] || !map[ny][nx]) continue;

						q.push({ny, nx, front.index});
						visited[ny][nx] = true;
						map[ny][nx] = front.index;
					}
				}
			}
		}
	}

	int minDist = INF;
	// 섬들의 모서리 찾아서 다리 연결한다.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!map[i][j]) continue;

			bool isEdge = false;
			// 상하좌우 살펴서 한 군데라도 뚫려있다면 모서리
			for (int d = 0; d < 4; d++) {
				int nx = j + dx[d];
				int ny = i + dy[d];

				if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
					if (map[ny][nx]) continue;

					isEdge = true;
					break;
				}
			}

			if (isEdge) {
				q.push({i, j, map[i][j], 0});
				memset(visited, 0, sizeof(visited));
			}

			while (!q.empty()) {
				auto front = q.front();
				q.pop();

				for (int d = 0; d < 4; d++) {
					int nx = front.x + dx[d];
					int ny = front.y + dy[d];

					if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
						if (visited[ny][nx] || map[ny][nx] == front.index) continue;
						if (map[ny][nx] && map[ny][nx] != front.index) {
							minDist = min(minDist, front.dist);
							break;
						}

						q.push({ny, nx, front.index, front.dist + 1});
						visited[ny][nx] = true;
					}
				}
			}
		}
	}

	cout << minDist;
	return 0;
}
