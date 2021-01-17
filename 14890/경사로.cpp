#include <iostream>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int reverseType[] = {1, 0, 3, 2};

int n, l;
int map[101][101];
bool connected[101][101][4];

int countMoveableRoad() {
	int result = 0;
	// 가로 검사
	for (int i = 0; i < n; i++) {
		bool flag = true;
		for (int j = 0; j < n - 1; j++) {
			// 같은 높이거나 연결되어 있다면
			if (map[i][j] == map[i][j + 1] || connected[i][j][0] || connected[i][j + 1][1]) continue;
			flag = false;
			break;
		}
		result += flag;
	}

	// 세로 검사
	for (int j = 0; j < n; j++) {
		bool flag = true;
		for (int i = 0; i < n - 1; i++) {
			// 같은 높이거나 연결되어 있다면
			if (map[i][j] == map[i + 1][j] || connected[i][j][2] || connected[i + 1][j][3]) continue;
			flag = false;
			break;
		}
		result += flag;
	}

	return result;
}

void dfs(int y, int x, int type) {
	// base case: 이미 연결된 경로라면
	if (connected[y][x][type]) return;

	int ny = y + dy[type];
	int nx = x + dx[type];
	// base case: 다음 위치가 지도를 벗어나는 경우
	if (nx < 0 || nx >= n || ny < 0 || ny >= n) return;

	// 다음 높이가 현재 높이와 같다면 바로 이동
	if (map[y][x] == map[ny][nx]) {
		dfs(ny, nx, type);
	}
	// 다음 높이가 현재 높이보다 한 칸 낮다면
	// 단, 이미 경사로가 설치되어 있으면 안된다.
	else if (map[y][x] == map[ny][nx] + 1) {
		// 경사로의 범위인 L만큼 검사
		bool flag = true;
		for (int i = 1; i <= l; i++) {
			ny = y + dy[type] * i;			
			nx = x + dx[type] * i;
			if (map[ny][nx] != map[y][x] - 1 || connected[ny][nx][type]) {
				flag = false;
				break;
			}
		}
		// 경사로를 설치할 수 있는 길이라면
		if (flag) {
			for (int i = 1; i <= l; i++) {
				ny = y + dy[type] * i;
				nx = x + dx[type] * i;
				connected[ny][nx][reverseType[type]] = true;
			}
			dfs(ny, nx, type);
		}
	}
}

void connectRoad() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// ↑ ↓
			dfs(i, j, 2);
			dfs(i, j, 3);

			// ← →
			dfs(i, j, 0);
			dfs(i, j, 1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> l;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	connectRoad();

	cout << countMoveableRoad();

	return 0;
}
