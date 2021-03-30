#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Coor {
	int y, x;
	Coor() {}
	Coor(int y, int x): y(y), x(x) {}
	bool operator==(Coor& a) { return y == a.y && x == a.x; }
};

struct Info {
	int itemSet;
	Coor coor;
	int time = 0;
	Info() {}
	Info(int itemSet, Coor coor): itemSet(itemSet), coor(coor) {}
	Info(int itemSet, int y, int x, int time): itemSet(itemSet), time(time) { coor = {y, x}; }
};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
	int n, m;
	cin >> n >> m;
	
	int map[50][50];
	int item = 1;
	Coor start, end;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			char c;
			cin >> c;
			
			if (c == '#') map[i][j] = -1;
			else if (c == '.') map[i][j] = 0;
			else if (c == 'S') {
				map[i][j] = 0;
				start = {i, j};
			}
			else if (c == 'X') map[i][j] = item++;
			else if (c == 'E') {
				map[i][j] = 0;
				end = {i, j};
			}
		}
	}
	
	queue<Info> bfs;
	bfs.emplace(0, start);
	
	int dp[50][50][1 << 5];
	memset(dp, 0x3f, sizeof(dp));
	dp[start.y][start.x][0] = 0;
	
	while (!bfs.empty()) {
		auto front = bfs.front();
		bfs.pop();
		
		for (int i = 0; i < 4; i++) {
			int nx = dx[i] + front.coor.x;
			int ny = dy[i] + front.coor.y;
			if (ny >= m || ny < 0 || nx >= n || nx < 0) continue;
			if (map[ny][nx] == -1) continue;
			
			int now = map[ny][nx];
			int itemSet = front.itemSet;
			if (now) itemSet |= 1 << (now - 1);
			if (dp[ny][nx][itemSet] <= front.time + 1) continue;
			
			bfs.emplace(itemSet, ny, nx, front.time + 1);
			dp[ny][nx][itemSet] = front.time + 1;
		}
	}
	
	cout << dp[end.y][end.x][(1 << (item - 1)) - 1];
	
	return 0;
}
