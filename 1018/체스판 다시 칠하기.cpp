#include <bits/stdc++.h>
using namespace std;

const int MAX = 987654321;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    char board[51][51];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    int answer = MAX;
    for (int i = 0; i <= n - 8; i++) {
        for (int j = 0; j <= m - 8; j++) {
            // (i, j)를 원점으로 8x8 사각형 검사
            // 원점이 B여야하는 경우
            int redrawB = 0;
            for (int r = i; r < i + 8; r++) {
                for (int c = j; c < j + 8; c++) {
                    // 홀수행이면 WBWBWBWB
                    if ((r - i) % 2) {
                        redrawB += (c - j) % 2 ? board[r][c] == 'W' : board[r][c] == 'B';
                    }
                    // 짝수행이면 BWBWBWBW
                    else {
                        redrawB += (c - j) % 2 ? board[r][c] == 'B' : board[r][c] == 'W';
                    }
                }
            }

            int redrawW = 0;
            // 원점이 W여야하는 경우
            for (int r = i; r < i + 8; r++) {
                for (int c = j; c < j + 8; c++) {
                    // 홀수행이면 BWBWBWBW
                    if ((r - i) % 2) {
                        redrawW += (c - j) % 2 ? board[r][c] == 'B' : board[r][c] == 'W';
                    }
                    // 짝수행이면 WBWBWBWB
                    else {
                        redrawW += (c - j) % 2 ? board[r][c] == 'W' : board[r][c] == 'B';
                    }
                }
            }

            answer = min(answer, min(redrawB, redrawW));
        }
    }

    cout << answer;
    return 0;
}
