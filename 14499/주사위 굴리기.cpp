#include <iostream>
using namespace std;

int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, -1, 1};

class Dice {
public:
	int left, top, back, bottom, front, right;

	// 북쪽
	// 아래 -> 앞, 앞 -> 위, 위 -> 뒤, 뒤 -> 아래
	int rollFront() {
		int beforeBottom = bottom;
		bottom = back;
		back = top;
		top = front;
		front = beforeBottom;
		return top;
	}

	// 남쪽
	// 앞 -> 아래, 아래 -> 뒤, 뒤 -> 위, 위 -> 앞
	int rollBack() {
		int beforeFront = front;
		front = top;
		top = back;
		back = bottom;
		bottom = beforeFront;
		return top;
	}

	// 동쪽
	// 오른쪽 -> 아래, 아래 -> 왼쪽, 왼쪽 -> 위, 위 -> 오른쪽
	int rollRight() {
		int beforeRight = right;
		right = top;
		top = left;
		left = bottom;
		bottom = beforeRight;
		return top;
	}

	// 서쪽
	// 왼쪽 -> 아래, 아래 -> 오른쪽, 오른쪽 -> 위, 위 -> 왼쪽
	int rollLeft() {
		int beforeLeft = left;
		left = top;
		top = right;
		right = bottom;
		bottom = beforeLeft;
		return top;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, x, y, k;
	cin >> n >> m >> y >> x >> k;

	int map[21][21];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	Dice dice {};
	for (int i = 0; i < k; i++) {
		int order;
		cin >> order;

		int nx = x + dx[order];
		int ny = y + dy[order];
		if (nx < m && nx >= 0 && ny < n && ny >= 0) {
			x = nx;
			y = ny;
			switch (order) {
				case 1:
					dice.rollRight();
					break;
				case 2:
					dice.rollLeft();
					break;
				case 3:
					dice.rollFront();
					break;
				case 4:
					dice.rollBack();
					break;
			}
		}
		else continue;

		if (!map[y][x]) map[y][x] = dice.bottom;
		else {
			dice.bottom = map[y][x];
			map[y][x] = 0;
		}

		cout << dice.top << ' ';
	}

	return 0;
}
