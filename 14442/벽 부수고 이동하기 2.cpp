#include <iostream>
#include <queue>
#include <algorithm>
#define INF 987654321
using namespace std;

struct coor {
	int y;
	int x;
	int dist;
	int brokeWall;
};

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, 1, -1, 0};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	bool map[1001][1001];
	char c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> c;
			map[i][j] = c == '1';
		}
	}

	int minDist = INF;
	queue<coor> q;
	bool visited[1001][1001][11] {};

	q.push({0, 0, 1, 0});
	visited[0][0][0] = true;

	while(!q.empty()) {
		auto front = q.front();
		q.pop();

		if (front.y == n - 1 && front.x == m - 1 && front.brokeWall <= k) {
			minDist = min(minDist, front.dist);
		}

		for (int i = 0; i < 4; i++) {
			int nx = front.x + dx[i];
			int ny = front.y + dy[i];

			if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
				if (map[ny][nx] && front.brokeWall < k) {
					if (!visited[ny][nx][front.brokeWall + 1]) {
						q.push({ny, nx, front.dist + 1, front.brokeWall + 1});
						visited[ny][nx][front.brokeWall + 1] = true;
						
					}
				}
				else if (!map[ny][nx]) {
					if (!visited[ny][nx][front.brokeWall]) {
						q.push({ny, nx, front.dist + 1, front.brokeWall});
						visited[ny][nx][front.brokeWall] = true;
					}
				}
			}
		}
	}

	cout << (minDist == INF ? -1 : minDist);
	return 0;
}
