#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
using namespace std;

class Cog {
private:
	bitset<8> status{};

public:
	void init(char status[]) {
		for (int i = 0; i < 8; i++) {
			this->status[i] = status[7 - i] - '0';
		}
	}

	void rotate(int dir) {
		if (dir == 1) {
			bool temp = status[0];
			status >>= 1;
			status[7] = temp;
		} else if (dir == -1) {
			bool temp = status[7];
			status <<= 1;
			status[0] = temp;
		}
	}

	bool getRight() {
		return status[5];
	}

	bool getLeft() {
		return status[1];
	}

	bool getTop() {
		return status[7];
	}
};

void rotate(Cog cogs[], int originIdx, int idx, int dir, int type) {
	// 오른쪽
	if (type == 1 && idx < 3) {
		// 맞닿은 극이 다르다면
		if (cogs[idx + 1].getLeft() ^ cogs[idx].getRight()) {
			rotate(cogs, originIdx, idx + 1, dir * -1, type);
		}
	}
	// 왼쪽
	if (type == -1 && idx > 0) {
		// 맞닿은 극이 다르다면
		if (cogs[idx - 1].getRight() ^ cogs[idx].getLeft()) {
			rotate(cogs, originIdx, idx - 1, dir * -1, type);
		}
	}
	// 가장 처음 시작한 톱니바퀴는 회전시키지 않음
	if (idx != originIdx) cogs[idx].rotate(dir);
}

int main() {
	Cog cogs[4];
	char status[9];
	for (int i = 0; i < 4; i++) {
		cin.getline(status, sizeof(status));
		cogs[i].init(status);
	}

	int k;
	cin >> k;

	for (int i = 0; i < k; i++) {
		int num, dir;
		cin >> num >> dir;
		--num;
		// 오른쪽
		rotate(cogs, num, num, dir, 1);
		// 왼쪽
		rotate(cogs, num, num, dir, -1);
		// 모두 회전시키고 나서 마지막에 돌린다.
		cogs[num].rotate(dir);
	}

	int score = 0;
	for (int i = 0; i < 4; i++) {
		if (cogs[i].getTop())
			score += int(pow(2, i));
	}

	cout << score;
	return 0;
}
