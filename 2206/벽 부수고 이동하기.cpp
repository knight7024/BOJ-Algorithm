#include <iostream>
#include <queue>
#include <algorithm>
#define INF 987654321

using namespace std;

struct Coor {
	int y;
	int x;
	bool brokeWall;
	int dist;
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	bool map[1001][1001];
	char c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> c;
			map[i][j] = c == '1';
		}
	}

	queue<Coor> q;
	bool visited[1001][1001][2] {};

	q.push({0, 0, 0, 0});
	visited[0][0][0] = true;

	int minDist = INF;
	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		// (N, M) 위치에 도착하면 최단 경로 업데이트
		if (front.y == n - 1 && front.x == m - 1)
			minDist = min(minDist, front.dist);

		for (int i = 0; i < 4; i++) {
			int nextX = front.x + dx[i];
			int nextY = front.y + dy[i];

			if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n) {
				// 다음 위치가 벽이라면
				if (map[nextY][nextX]) {
					// 벽을 부순 적이 없고 방문한 적이 없는 위치라면
					if (!visited[nextY][nextX][front.brokeWall] && !front.brokeWall) {
						// 벽을 부쉈다고 체크한 뒤 큐에 넣는다.
						q.push({nextY, nextX, true, front.dist + 1});
						visited[nextY][nextX][true] = true;
					}
				}
				// 다음 위치가 이동 가능한 곳이라면
				else {
					// 방문한 적이 있다면 패스한다.
					if (visited[nextY][nextX][front.brokeWall]) continue;

					// 다음 좌표를 큐에 넣는다.
					q.push({nextY, nextX, front.brokeWall, front.dist + 1});
					visited[nextY][nextX][front.brokeWall] = true;
				}
			}
		}
	}
	cout << (minDist == INF ? -1 : minDist + 1);
	return 0;
}
