#include <iostream>
#include <algorithm>
#define INF 987654321

using namespace std;

bool btns[10];

int isPossibleCh(int ch) {
	if (!ch) return btns[0] ? -1 : 1;

	int size = 0;
	while (ch) {
		if (btns[ch % 10]) return -1;
		ch /= 10;
		size++;
	}
	return size;
}

int main() {
	int n;
	cin >> n;

	int broken;
	cin >> broken;

	int ch;
	for (int i = 0; i < broken; i++) {
		cin >> ch;
		btns[ch] = true;
	}

	int move = INF;
	for (int i = 0; i <= 1000000; i++) {
		int tempMove = INF;
		// 이동 가능한 채널이면
		int moveResult = isPossibleCh(i);
		if (moveResult != -1) {
			// 버튼을 눌러서 이동하는 경우와
			tempMove = min(tempMove, moveResult);
		}
		// 직접 이동하는 경우 중 최솟값 구한다.
		tempMove = min(tempMove, abs(100 - i));

		// 그 이후 N으로 이동한다.
		move = min(move, tempMove + abs(i - n));
	}
	cout << move;
}
