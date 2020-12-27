#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define MAX 987654321
using namespace std;

struct Coor {
	int y;
	int x;
	bool operator==(Coor& a) { return y == a.y && x == a.x; }
	Coor operator+(Coor& a) { return {y + a.y, x + a.x}; }
	Coor operator*(int a) { return {y * a, x * a}; }
};

struct Move {
	int moveCount;
	int lastDirIdx;
};

Coor dir[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int n, m;
char map[11][11];
Coor holeCoor;
int answer = MAX;

void dfs(Coor redCoor, Coor blueCoor, int count, int lastDirIdx) {
	// 빨간 구슬이 구멍에 도착한 경우
	if (redCoor == holeCoor) {
		// 파란 구슬이 떨어질 수 있으면 불가능
		Coor revDirCoor = dir[lastDirIdx] * -1;
		if (holeCoor + revDirCoor == blueCoor) return;
		answer = min(answer, count);
		return;
	}

	if (count >= 10) return;

	for (int i = 0; i < 4; i++) {
		Coor dirCoor = dir[i];
		Coor nextRedCoor = redCoor, nextBlueCoor = blueCoor;
		// 상하
		if (dirCoor.y) {
			// 이동하려는 방향에서 빨간 구슬이 파란 구슬보다 먼저 이동하는지 여부
			bool redPrior = (redCoor.y - blueCoor.y) * dirCoor.y > 0;
			
			if (redPrior) {
				for (int i = redCoor.y; ; i += dirCoor.y) {
					if (nextRedCoor == holeCoor) break;
					if (i >= n || i < 0) break;
					if (map[i][redCoor.x] == '#') break;
					nextRedCoor.y = i;
				}
				for (int i = blueCoor.y; ; i += dirCoor.y) {
					if (nextBlueCoor == holeCoor) break;
					if (i >= n || i < 0) break;
					if ((i == nextRedCoor.y && redCoor.x == blueCoor.x) || map[i][blueCoor.x] == '#') break;
					nextBlueCoor.y = i;
				}
			}
			else {
				for (int i = blueCoor.y; ; i += dirCoor.y) {
					if (nextBlueCoor == holeCoor) break;
					if (i >= n || i < 0) break;
					if (map[i][blueCoor.x] == '#') break;
					nextBlueCoor.y = i;
				}
				for (int i = redCoor.y; ; i += dirCoor.y) {
					if (nextRedCoor == holeCoor) break;
					if (i >= n || i < 0) break;
					if ((i == nextBlueCoor.y && redCoor.x == blueCoor.x) || map[i][redCoor.x] == '#') break;
					nextRedCoor.y = i;
				}
			}
		}
		// 좌우
		else if (dirCoor.x) {
			// 이동하려는 방향에서 빨간 구슬이 파란 구슬보다 먼저 이동하는지 여부
			bool redPrior = (redCoor.x - blueCoor.x) * dirCoor.x > 0;

			if (redPrior) {
				for (int i = redCoor.x; ; i += dirCoor.x) {
					if (nextRedCoor == holeCoor) break;
					if (i >= m || i < 0) break;
					if (map[redCoor.y][i] == '#') break;
					nextRedCoor.x = i;
				}
				for (int i = blueCoor.x; ; i += dirCoor.x) {
					if (nextBlueCoor == holeCoor) break;
					if (i >= m || i < 0) break;
					if ((i == nextRedCoor.x && redCoor.y == blueCoor.y) || map[blueCoor.y][i] == '#') break;
					nextBlueCoor.x = i;
				}
			}
			else {
				for (int i = blueCoor.x; ; i += dirCoor.x) {
					if (nextBlueCoor == holeCoor) break;
					if (i >= m || i < 0) break;
					if (map[blueCoor.y][i] == '#') break;
					nextBlueCoor.x = i;
				}
				for (int i = redCoor.x; ; i += dirCoor.x) {
					if (nextRedCoor == holeCoor) break;
					if (i >= m || i < 0) break;
					if ((i == nextBlueCoor.x && redCoor.y == blueCoor.y) || map[redCoor.y][i] == '#') break;
					nextRedCoor.x = i;
				}
			}
		}

		dfs(nextRedCoor, nextBlueCoor, count + 1, i);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;

	Coor redCoor, blueCoor;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') redCoor = {i, j};
			else if (map[i][j] == 'B') blueCoor = {i, j};
			else if (map[i][j] == 'O') holeCoor = {i, j};
		}
	}

	dfs(redCoor, blueCoor, 0, -1);

	cout << (answer == MAX ? -1 : answer);

	return 0;
}
