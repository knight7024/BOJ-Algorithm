#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Loc {
	int y;
	int x;
};

struct State {
	Loc nowLoc;
	int size;
	int eatCount;
	int dist;
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	Loc baby {};
	int space[21][21];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> space[i][j];
			// 공간의 상태가 9면 아기 상어의 위치
			if (space[i][j] == 9) {
				baby = {i, j};
				space[i][j] = 0;
			}
		}
	}

	queue<State> q;
	bool visited[21][21];
	State minDist[401];
	bool motherShark = false;
	State init = {baby, 2, 0, 0};
	int answer = 0;

	while (!motherShark) {
		memset(visited, 0, sizeof(visited));
		memset(minDist, -1, sizeof(minDist));

		q.push(init);
		motherShark = true;
		visited[init.nowLoc.y][init.nowLoc.x] = true;

		while (!q.empty()) {
			auto front = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				// 상하좌우 다음 위치
				int nextX = front.nowLoc.x + dx[i];
				int nextY = front.nowLoc.y + dy[i];

				if (nextX < n && nextX >= 0 && nextY < n && nextY >= 0) {
					if (visited[nextY][nextX]) continue;

					int status = space[nextY][nextX];
					// 다음 공간의 상태가 현재 상어의 사이즈보다 작다면,
					// 빈 칸 or 작은 물고기들 (단, 동일한 사이즈의 물고기는 먹을 수 없다.)
					if (status <= front.size) {
						int nextDist = front.dist + 1;
						State nextState = {{nextY, nextX}, front.size, front.eatCount, nextDist};
						if (status && status < nextState.size) {
							// 만약 상어가 물고기를 먹었으면
							// 엄마 상어 호출 안 해도 된다, 먹은 카운트 늘려준다.
							motherShark = false;
							++nextState.eatCount;
							// 자기 크기만큼 먹었으면, 크기 늘려준다.
							if (nextState.eatCount == nextState.size) {
								nextState.eatCount = 0;
								++nextState.size;
							}

							// 거리가 가까운 물고기가 많다면,
							if (minDist[nextDist].nowLoc.y != -1 && minDist[nextDist].nowLoc.x != -1) {
								// 가장 위에 있는 물고기가 여러마리라면,
								if (minDist[nextDist].nowLoc.y == nextY) {
									// 가장 왼쪽에 있는 물고기를 먹는다.
									if (minDist[nextDist].nowLoc.x > nextX) {
										minDist[nextDist] = nextState;
									}
								}
								// 가장 위에 있는 물고기를 먹는다.
								else if (minDist[nextDist].nowLoc.y > nextY) {
									minDist[nextDist] = nextState;
								}
							}
							// 거리가 가장 가까운 물고기를 먹으러 간다.
							else {
								minDist[nextDist] = nextState;
							}
						}
						q.push(nextState);
						visited[nextY][nextX] = true;
					}
				}
			}
		}

		// 가장 거리가 가까운 물고기 탐색
		for (int i = 0; i <= 400; i++) {
			if (minDist[i].nowLoc.y != -1 && minDist[i].nowLoc.x != -1) {
				init = minDist[i];
				answer += init.dist;
				init.dist = 0;
				// 먹은 물고기 공간은 빈 칸으로 변경해준다.
				space[init.nowLoc.y][init.nowLoc.x] = 0;
				break;
			}
		}
	}
	cout << answer;
}
