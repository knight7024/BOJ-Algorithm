#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int, int> PAIRII;

int room[51][51];
int roomMinus[51][51];
int roomPlus[51][51];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void init() {
	// 초기화
	memset(roomMinus, 0, sizeof(roomMinus));
	memset(roomPlus, 0, sizeof(roomPlus));
}

void spreadDust(int r, int c) {
	// 미세먼지는 네 방향으로 확산된다.
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (room[i][j] == -1) continue;

			// 확산되는 양은 1/5이다.
			int spread = room[i][j] / 5;
			for (int k = 0; k < 4; k++) {
				int nx = j + dx[k];
				int ny = i + dy[k];
				// 공기청정기가 있거나 칸이 없다면 확산되지 않는다.
				if (room[ny][nx] == -1 || ny >= r || ny < 0 || nx >= c || nx < 0) continue;

				// 합쳐질 먼지의 양과 확산되어서 줄어든 먼지의 양을 각각 저장한다.
				roomPlus[ny][nx] += spread;
				roomMinus[i][j] += spread;
			}
		}
	}
}

void airCleaner(int r, int c, PAIRII airCleanerLoc[]) {
	// 위쪽 공기청정기의 바람은 반시계방향으로 순환
	PAIRII& top = airCleanerLoc[0];

	// 공기청정기의 위치로부터 시계방향으로 돌면서 먼지의 위치를 1칸씩 이동시킨다.
	// ↑
	for (int i = top.first; i > 0; i--) {
		// 공기청정기로 들어간 미세먼지는 모두 정화된다.
		if (i == top.first) {
			room[i - 1][top.second] = 0;
			continue;
		}
		swap(room[i][top.second], room[i - 1][top.second]);
	}

	// →
	for (int j = top.second; j < c - 1; j++) {
		swap(room[0][j], room[0][j + 1]);
	}

	// ↓
	for (int i = 0; i < top.first; i++) {
		swap(room[i][c - 1], room[i + 1][c - 1]);
	}

	// ←
	for (int j = c - 1; j > top.second; j--) {
		if (j - 1 == top.second) continue;
		swap(room[top.first][j], room[top.first][j - 1]);
	}


	// 아래쪽 공기청정기의 바람은 시계방향으로 순환
	PAIRII& bottom = airCleanerLoc[1];

	// 공기청정기의 위치로부터 반시계방향으로 돌면서 먼지의 위치를 1칸씩 이동시킨다.
	// ↓
	for (int i = bottom.first; i < r - 1; i++) {
		// 공기청정기로 들어간 미세먼지는 모두 정화된다.
		if (i == bottom.first) {
			room[i + 1][bottom.second] = 0;
			continue;
		}
		swap(room[i][bottom.second], room[i + 1][bottom.second]);
	}

	// →
	for (int j = bottom.second; j < c - 1; j++) {
		swap(room[r - 1][j], room[r - 1][j + 1]);
	}

	// ↑
	for (int i = r - 1; i > bottom.first; i--) {
		swap(room[i][c - 1], room[i - 1][c - 1]);
	}

	// ←
	for (int j = c - 1; j > bottom.second; j--) {
		if (j - 1 == bottom.second) continue;
		swap(room[bottom.first][j], room[bottom.first][j - 1]);
	}
}

void apply(int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (room[i][j] == -1) continue;

			// 확산된 먼지만큼 줄어들고 합쳐진 먼지만큼 늘어난다.
			room[i][j] += roomPlus[i][j];
			room[i][j] -= roomMinus[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int r, c, t;
	cin >> r >> c >> t;

	int airCleanerIdx = 0;
	PAIRII airCleanerLoc[2];
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> room[i][j];
			// 공기청정기의 좌표 저장
			if (room[i][j] == -1) {
				airCleanerLoc[airCleanerIdx++] = {i, j};
			}
		}
	}

	//1초 동안 아래의 일들이 진행된다.
	while (t--) {
		init();
		// 미세먼지가 확산된다.
		spreadDust(r, c);
		// 수행된 결과를 적용한다.
		apply(r, c);
		// 공기청정기가 작동한다.
		airCleaner(r, c, airCleanerLoc);
	}

	int dust = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (room[i][j] == -1) continue;
			dust += room[i][j];
		}
	}

	cout << dust;
	return 0;
}
