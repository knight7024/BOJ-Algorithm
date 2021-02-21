#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

int sudoku[10][10];
// 스도쿠의 가로를 비트마스킹한 배열
int bitHor[10];
// 스도쿠의 세로를 비트마스킹한 배열
int bitVer[10];
// 스도쿠의 3x3 구역을 비트마스킹한 배열
// (i / 3) * 3 + (j / 3) 
int bitDiv[10];
vector <pair<int, int>> blank;

bool isValidSudoku(int n, int r, int c) {
    // 가로줄 검사
    if (bitHor[r] & (1 << n)) return false;
    // 세로줄 검사
    if (bitVer[c] & (1 << n)) return false;
    // 3x3 정사각형 검사
    if (bitDiv[(r / 3) * 3 + (c / 3)] & (1 << n)) return false;

    return true;
}

bool playSudoku(int n) {
    // base case
    if (n >= blank.size()) return true;

    // 스도쿠 빈 칸 좌표
    int r = blank[n].first, c = blank[n].second;
    for (int i = 1; i <= 9; i++) {
        // 올바른 스도쿠라면 다음 빈 칸으로 이동한다.
        if (isValidSudoku(i, r, c)) {
            sudoku[r][c] = i;
            bitHor[r] |= 1 << i;
            bitVer[c] |= 1 << i;
            bitDiv[(r / 3) * 3 + (c / 3)] |= 1 << i;

            if (playSudoku(n + 1)) return true;

            bitDiv[(r / 3) * 3 + (c / 3)] &= ~(1 << i);
            bitVer[c] &= ~(1 << i);
            bitHor[r] &= ~(1 << i);
            sudoku[r][c] = 0;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int number;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> number;
            if (!number) {
                blank.emplace_back(i, j);
                continue;
            }
            sudoku[i][j] = number;
            bitHor[i] |= 1 << number;
            bitVer[j] |= 1 << number;
            bitDiv[(i / 3) * 3 + (j / 3)] |= 1 << number;
        }
    }

    playSudoku(0);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
