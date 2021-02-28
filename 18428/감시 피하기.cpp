#include <iostream>
#include <queue>
#define OBSTACLE 3
using namespace std;

const int dy[] = {0, 0, -1, 1};
const int dx[] = {-1, 1, 0, 0};

struct Check {
	int y, x;
	int dir;
	Check() {}
	Check(int y, int x, int dir): y(y), x(x), dir(dir) {}
};

int n;
char map[10][10];
vector<pair<int, int>> student;
vector<pair<int, int>> blank;

bool bfs() {
	queue<Check> bfs;
	for (auto& p : student) {
		for (int i = 0; i < 4; i++) {
			bfs.emplace(p.first, p.second, i);
		}
	}

	while (!bfs.empty()) {
		auto front = bfs.front();
		bfs.pop();

		int ny = front.y + dy[front.dir];
		int nx = front.x + dx[front.dir];
		if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;

		if (map[ny][nx] == 'O') continue;
		if (map[ny][nx] == 'T') return false;

		bfs.emplace(ny, nx, front.dir);
	}

	return true;
}

void combination(int idx, int depth) {
	if (depth == OBSTACLE) {
		if (bfs()) {
			cout << "YES";
			exit(0);
		}
		return;
	}

	for (int i = idx; i < blank.size(); i++) {
		map[blank[i].first][blank[i].second] = 'O';
		combination(i + 1, depth + 1);
		map[blank[i].first][blank[i].second] = 'X';
	}
}

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'X') blank.emplace_back(i, j);
			else if (map[i][j] == 'S') student.emplace_back(i, j);
		}
	}

	combination(0, 0);

	cout << "NO";

    return 0;
}
