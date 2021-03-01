#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Fish {
	int id;
	int y, x;
	int dir;
	bool isDead = false;
	Fish() {}
	Fish(int id, int y, int x, int dir): id(id), y(y), x(x), dir(dir) {}
	bool operator<(const Fish& a) { return id < a.id; }
};

// 12시를 기준으로 45도 반시계
const int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

void moveFish(vector<Fish>& fishes, int space[4][4]) {
	for (Fish& f : fishes) {
		if (f.isDead) continue;
		// 각 물고기는 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전시킨다.
		for (int i = 0; i < 8; i++) {
			int newDir = (f.dir + i) % 8;
			int ny = f.y + dy[newDir];
			int nx = f.x + dx[newDir];
			// 상어가 있거나, 공간의 경계를 넘거나
			if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4 || space[ny][nx] == -1) continue;

			// 빈 공간으로 이동
			if (!space[ny][nx]) {
				swap(space[f.y][f.x], space[ny][nx]);
				f = {f.id, ny, nx, newDir};
				break;
			}

			// 물고기가 다른 물고기가 있는 칸으로 이동할 때는 서로의 위치를 바꾸는 방식
			Fish& target = *lower_bound(fishes.begin(), fishes.end(), Fish(space[ny][nx], 0, 0, 0));
			swap(space[f.y][f.x], space[ny][nx]);
			swap(f.y, target.y);
			swap(f.x, target.x);
			f.dir = newDir;
			break;
		}
	}
}

int dfs(vector<Fish>& fishes, int space[4][4], Fish& shark) {
	vector<Fish> copyFishes(fishes);
	int copySpace[4][4];
	copy(&space[0][0], &space[3][4], &copySpace[0][0]);
	Fish copyShark = shark;

	moveFish(copyFishes, copySpace);

	// 물고기의 이동이 모두 끝나면 상어가 이동한다.
	// 한 번에 여러 개의 칸을 이동할 수 있다.
	int ate = 0;
	for (int i = 1; i < 4; i++) {
		int ny = copyShark.y + dy[copyShark.dir] * i;
		int nx = copyShark.x + dx[copyShark.dir] * i;
		if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) break;
		// 물고기가 없는 칸으로는 이동할 수 없다.
		if (copySpace[ny][nx] <= 0) continue;

		// 그 칸에 있는 물고기를 먹고, 그 물고기의 방향을 가지게 된다.
		Fish& target = *lower_bound(copyFishes.begin(), copyFishes.end(), Fish(copySpace[ny][nx], 0, 0, 0));
		copySpace[shark.y][shark.x] = 0;
		copySpace[ny][nx] = -1;
		copyShark = {-1, ny, nx, target.dir};
		target.isDead = true;
		ate = max(ate, dfs(copyFishes, copySpace, copyShark) + target.id);
		target.isDead = false;
		copyShark = shark;
		copySpace[ny][nx] = target.id;
		copySpace[shark.y][shark.x] = -1;
	}

	return ate;
}

int main() {
	vector<Fish> fishes;
	int space[4][4];
	Fish shark;
	int firstFishId = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int a, b;
			cin >> a >> b;
			// 상어의 방향은 (0, 0)에 있던 물고기의 방향과 같다.
			if (i == 0 && j == 0) {
				firstFishId = a;
				shark = {-1, i, j, b - 1};
				space[i][j] = -1;
				continue;
			}
			fishes.emplace_back(a, i, j, b - 1);
			space[i][j] = a;
		}
	}

	// 물고기는 번호가 작은 물고기부터 순서대로 이동한다.
	sort(fishes.begin(), fishes.end());

	cout << dfs(fishes, space, shark) + firstFishId;

	return 0;
}
