#include <iostream>
#include <cstring>
#include <algorithm>
#define MAXSIZE 21
#define MAXMOVE 5
using namespace std;

int n;
bool isMerged[MAXSIZE][MAXSIZE];
int maxBlock = -1;

// ↑
void moveUp(int board[][MAXSIZE]) {
	memset(isMerged, 0, sizeof(isMerged));

	for (int j = 0; j < n; j++) {
		for (int i = 1; i < n; i++) {
			// 빈 공간이면 넘어간다.
			if (!board[i][j]) continue;

			// 위 칸이 막힌 공간 또는 빈 공간일 때까지 옮긴다.
			int tempI = i;
			while (tempI >= 1 && !board[tempI - 1][j]) {
				swap(board[tempI][j], board[tempI - 1][j]);
				--tempI;
			}

			// 위 칸이 블록이고 합쳐진 적 없는 수이며 같은 수라면 합칠 수 있다.
			if (tempI >= 1 && !isMerged[tempI - 1][j] && board[tempI - 1][j] == board[tempI][j]) {
				board[tempI][j] = 0;
				board[tempI - 1][j] *= 2;
				isMerged[tempI - 1][j] = true;
			}
		}
	}
}

// ↓
void moveDown(int board[][MAXSIZE]) {
	memset(isMerged, 0, sizeof(isMerged));

	for (int j = 0; j < n; j++) {
		for (int i = n - 2; i >= 0; i--) {
			// 빈 공간이면 넘어간다.
			if (!board[i][j]) continue;

			// 아래 칸이 막힌 공간 또는 빈 공간일 때까지 옮긴다.
			int tempI = i;
			while (tempI <= n - 2 && !board[tempI + 1][j]) {
				swap(board[tempI][j], board[tempI + 1][j]);
				++tempI;
			}

			// 아래 칸이 블록이고 합쳐진 적 없는 수이며 같은 수라면 합칠 수 있다.
			if (tempI <= n - 2 && !isMerged[tempI + 1][j] && board[tempI + 1][j] == board[tempI][j]) {
				board[tempI][j] = 0;
				board[tempI + 1][j] *= 2;
				isMerged[tempI + 1][j] = true;
			}
		}
	}
}

// ←
void moveLeft(int board[][MAXSIZE]) {
	memset(isMerged, 0, sizeof(isMerged));

	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n; j++) {
			// 빈 공간이면 넘어간다.
			if (!board[i][j]) continue;

			// 왼쪽 칸이 막힌 공간 또는 빈 공간일 때까지 옮긴다.
			int tempJ = j;
			while (tempJ >= 1 && !board[i][tempJ - 1]) {
				swap(board[i][tempJ], board[i][tempJ - 1]);
				--tempJ;
			}

			// 왼쪽 칸이 블록이고 합쳐진 적 없는 수이며 같은 수라면 합칠 수 있다.
			if (tempJ >= 1 && !isMerged[i][tempJ - 1] && board[i][tempJ - 1] == board[i][tempJ]) {
				board[i][tempJ] = 0;
				board[i][tempJ - 1] *= 2;
				isMerged[i][tempJ - 1] = true;
			}
		}
	}
}

// →
void moveRight(int board[][MAXSIZE]) {
	memset(isMerged, 0, sizeof(isMerged));

	for (int i = 0; i < n; i++) {
		for (int j = n - 2; j >= 0; j--) {
			// 빈 공간이면 넘어간다.
			if (!board[i][j]) continue;

			// 오른쪽 칸이 막힌 공간 또는 빈 공간일 때까지 옮긴다.
			int tempJ = j;
			while (tempJ <= n - 2 && !board[i][tempJ + 1]) {
				swap(board[i][tempJ], board[i][tempJ + 1]);
				++tempJ;
			}

			// 오른쪽 칸이 블록이고 합쳐진 적 없는 수이며 같은 수라면 합칠 수 있다.
			if (tempJ <= n - 2 && !isMerged[i][tempJ + 1] && board[i][tempJ + 1] == board[i][tempJ]) {
				board[i][tempJ] = 0;
				board[i][tempJ + 1] *= 2;
				isMerged[i][tempJ + 1] = true;
			}
		}
	}
}

void backtracking(int limit, int board[][MAXSIZE]) {
	// 모든 이동을 완료했다면 가장 큰 블록 찾는다.
	if (!limit) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				maxBlock = max(maxBlock, board[i][j]);
			}
		}
		return;
	}

	// 현재 보드는 따로 저장해둔다.
	int prevBoard[MAXSIZE][MAXSIZE];
	copy(&board[0][0], &board[n][n], &prevBoard[0][0]);

	moveUp(board);
	backtracking(limit - 1, board);
	copy(&prevBoard[0][0], &prevBoard[n][n], &board[0][0]);

	moveDown(board);
	backtracking(limit - 1, board);
	copy(&prevBoard[0][0], &prevBoard[n][n], &board[0][0]);

	moveLeft(board);
	backtracking(limit - 1, board);
	copy(&prevBoard[0][0], &prevBoard[n][n], &board[0][0]);

	moveRight(board);
	backtracking(limit - 1, board);
	copy(&prevBoard[0][0], &prevBoard[n][n], &board[0][0]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	int board[MAXSIZE][MAXSIZE];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
		}
	}

	backtracking(MAXMOVE, board);

	cout << maxBlock;
	return 0;
}
