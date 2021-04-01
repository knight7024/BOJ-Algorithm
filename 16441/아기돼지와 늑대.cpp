#include <iostream>
#include <vector>
#include <queue>
#define endl '\n'
using namespace std;

struct Coor {
	int y, x;
	Coor() {}
	Coor(int y, int x): y(y), x(x) {}
};

struct Wolf {
	Coor coor;
	int dir = -1;
	Wolf() {}
	Wolf(int y, int x, int dir): dir(dir){ coor = {y, x}; }
};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
	int n, m;
	cin >> n >> m;
	
	char map[100][100];
	vector<Coor> wolves;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'W') wolves.emplace_back(i, j);
		}
	}
	
	queue<Wolf> bfs;
	bool visited[100][100][4] {};
	
	for (auto& w : wolves) {
		bfs.emplace(w.y, w.x, -1);
		for (int i = 0; i < 4; i++) visited[w.y][w.x][i] = true;
	}
	
	while (!bfs.empty()) {
		auto front = bfs.front();
		bfs.pop();
		
		int y = front.coor.y;
		int x = front.coor.x;
		
		// 얼음을 이동 중인 상태: Wolf의 dir이 -1이 아니다.
		if (front.dir != -1) {
			int ny = y + dy[front.dir];
			int nx = x + dx[front.dir];
			
			if (ny >= n || ny < 0 || nx >= m || nx < 0) continue;
			if (visited[ny][nx][front.dir]) continue;
			// 산에 부딪힌 늑대는 다시 이동 가능
			if (map[ny][nx] == '#') goto exitif;
			
			// 다음 경로도 얼음인지 확인한다.
			bfs.emplace(ny, nx, map[ny][nx] == '+' ? front.dir : -1);
			visited[ny][nx][front.dir] = true;
			continue;
		}
	exitif:
		// 초원을 이동 중인 상태
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			
			if (ny >= n || ny < 0 || nx >= m || nx < 0) continue;
			if (map[ny][nx] == '#' || visited[ny][nx][i]) continue;
			
			// 다음 경로도 얼음인지 확인한다.
			bfs.emplace(ny, nx, map[ny][nx] == '+' ? i : -1);
			visited[ny][nx][i] = true;
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == '#') cout << '#';
			else if (visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3] || map[i][j] != '.') cout << map[i][j];
			else cout << 'P';
		}
		cout << endl;
	}
	
	return 0;
}
