#include <iostream>
#include <algorithm>
#define INF 987654321
using namespace std;

bool paper[15][15];
int paperLimit[] = {0, 5, 5, 5, 5, 5};
int minPaperCount = INF;
int blankCount = 0;

bool canCover(int r, int c, int size) {
	for (int i = r; i < r + size; i++) {
		if (i > 9) return false;
		for (int j = c; j < c + size; j++) {
			if (j > 9) return false;
			if (!paper[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void backtracking(int r, int c, int paperCount) {
	if (r > 9) return;
	if (c > 9) {
		backtracking(r + 1, 0, paperCount);
		return;
	}
	if (!paper[r][c]) {
		backtracking(r, c + 1, paperCount);
		return;
	}

	for (int size = 1; size <= 5; size++) {
		if (!canCover(r, c, size)) continue;
		if (!paperLimit[size]) continue;

		int nowBlankSpace = 0;
		for (int i = r; i < r + size; i++) {
			for (int j = c; j < c + size; j++) {
				nowBlankSpace += paper[i][j];
				paper[i][j] = 0;
			}
		}

		int nowPaperCount = paperCount + 1;
		blankCount -= nowBlankSpace;
		paperLimit[size]--;
		if (!blankCount) {
			minPaperCount = min(minPaperCount, nowPaperCount);
		}
		backtracking(r, c + 1, nowPaperCount);


		for (int i = r; i < r + size; i++) {
			for (int j = c; j < c + size; j++) {
				paper[i][j] = 1;
			}
		}
		blankCount += nowBlankSpace;
		paperLimit[size]++;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> paper[i][j];
			if (paper[i][j]) blankCount++;
		}
	}

	if (!blankCount) minPaperCount = 0;
	else backtracking(0, 0, 0);

	cout << (minPaperCount == INF ? -1 : minPaperCount);
	return 0;
}
