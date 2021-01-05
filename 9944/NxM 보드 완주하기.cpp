#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX 987654321
#define endl '\n'
using namespace std;

struct Coor {
	int y;
	int x;
	Coor operator+(Coor& a) { return Coor({y + a.y, x + a.x}); }
	void operator+=(Coor& a) { y += a.y; x += a.x; }
	bool operator==(Coor& a) { return y == a.y && x == a.x; }
	bool operator!=(Coor& a) { return !(*this == a); }
};

int n, m;
char map[30][30];
int blankCount;
int visitCount;
bool visited[30][30];
int answer = MAX;

bool isAccessible(Coor coor) {
	return coor.y >= 0 && coor.y < n && coor.x >= 0 && coor.x < m && map[coor.y][coor.x] != '*' && !visited[coor.y][coor.x];
}

Coor moveBall(Coor now, Coor dir) {
	while (isAccessible(now + dir)) {
		visited[now.y][now.x] = true;
		now += dir;
		visitCount++;
	}

	return now;
}

void revertBall(Coor to, Coor from, Coor dir) {
	while (to != from) {
		visited[from.y][from.x] = false;
		from += dir;
		visitCount--;
	}
}

void dfs(Coor now, int depth) {
	// 가지치기
	if (visitCount > blankCount) return;
	
	// 모든 칸을 순회했다면
	if (visitCount == blankCount) {
		answer = min(answer, depth);
		return;
	}
	
	// ↑
	Coor upside = moveBall(now, {-1, 0});
	if (upside != now) {
		dfs(upside, depth + 1);
		revertBall(now, upside, {1, 0});
	}

	// ↓
	Coor downside = moveBall(now, {1, 0});
	if (downside != now) {
		dfs(downside, depth + 1);
		revertBall(now, downside, {-1, 0});
	}

	// ←
	Coor leftside = moveBall(now, {0, -1});
	if (leftside != now) {
		dfs(leftside, depth + 1);
		revertBall(now, leftside, {0, 1});
	}

	// →
	Coor rightside = moveBall(now, {0, 1});
	if (rightside != now) {
		dfs(rightside, depth + 1);
		revertBall(now, rightside, {0, -1});
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int tc = 1;
	// 입력이 없을 때까지
	while (cin >> n >> m) {
		blankCount = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> map[i][j];
				blankCount += map[i][j] == '.';
			}
		}

		answer = MAX;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == '*') continue;
				memset(visited, 0, sizeof(visited));
				visitCount = 1;
				dfs({i, j}, 0);
			}
		}

		cout << "Case " << tc++ << ": " << (answer == MAX ? -1 : answer) << endl;
	}

	return 0;
}
