#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

struct State {
	int y;
	int x;
	int dir;
	int orderCount = 0;
	State() {}
	State(int y, int x, int dir, int orderCount): y(y), x(x), dir(dir), orderCount(orderCount) {}
	bool operator==(State a) { return y == a.y && x == a.x; } 
};

// 1: 동, 2: 서, 3: 남, 4: 북
int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};
// [A][B]: A에서 B로 회전시킬 때 필요한 명령의 횟수
int dirOrderCount[5][5] = {
	{0, 0, 0, 0, 0},
	{0, 0, 2, 1, 1},
	{0, 2, 0, 1, 1},
	{0, 1, 1, 0, 2},
	{0, 1, 1, 2, 0},
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int m, n;
	cin >> m >> n;

	bool factory[101][101];
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> factory[i][j];
		}
	}

	State from, to;
	cin >> from.y >> from.x >> from.dir;
	cin >> to.y >> to.x >> to.dir;

	int dp[101][101][5];
	memset(dp, INF, sizeof(dp));

	queue<State> q;
	q.emplace(from);
	dp[from.y][from.x][from.dir] = 0;

	int answer = INF;
	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		if (front == to) {
			answer = min(answer, front.orderCount + dirOrderCount[front.dir][to.dir]);
			continue;
		}

		// 방향 전환
		for (int d = 1; d <= 4; d++) {
			// k칸 움직일 수 있는 명령
			int nextOrderCount = front.orderCount + dirOrderCount[front.dir][d] + 1;
			for (int k = 1; k <= 3; k++) {
				int nx = front.x + k * dx[d];
				int ny = front.y + k * dy[d];
				// 공장을 벗어나거나 궤도가 아니라면
				if (ny <= 0 || ny > m || nx <= 0 || nx > n || factory[ny][nx]) break;
				if (dp[ny][nx][d] <= nextOrderCount) continue;
				q.emplace(ny, nx, d, nextOrderCount);
				dp[ny][nx][d] = nextOrderCount;
			}
		}
	}

	cout << answer;

	return 0;
}
