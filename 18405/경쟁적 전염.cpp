#include <iostream>
#include <queue>
using namespace std;

struct Virus {
	int y, x;
	int type;
	int time;
	Virus() {}
	Virus(int y, int x, int type, int time): y(y), x(x), type(type), time(time) {}
};

struct cmp {
	bool operator()(Virus& a, Virus& b) {
		if (a.time == b.time) return a.type > b.type;
		return a.time > b.time;
	}
};

const int dy[] = {0, 0, -1, 1};
const int dx[] = {-1, 1, 0, 0};

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	int board[200][200];
	priority_queue<Virus, vector<Virus>, cmp> pq;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
			if (board[i][j]) pq.emplace(i, j, board[i][j], 1);
		}
	}

	int s, x, y;
	cin >> s >> x >> y;

	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();

		if (front.time > s) break;

		for (int i = 0; i < 4; i++) {
			int ny = front.y + dy[i];
			int nx = front.x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (board[ny][nx]) continue;
			
			board[ny][nx] = front.type;
			pq.emplace(ny, nx, front.type, front.time + 1);
		}
	}

	cout << board[x - 1][y - 1];

    return 0;
}
