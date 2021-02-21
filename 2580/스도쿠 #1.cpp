#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define endl '\n'

using namespace std;

vector<pair<int, int>> blank;
int sudoku[10][10];
bool check[10];

bool isValidSudoku(int n, int r, int c) {
    // 가로줄 검사
    memset(check, 0, sizeof(check));
    check[n] = true;
    for (int i = 0; i < 9; i++) {
        int num = sudoku[r][i];
        if (!num) continue;
        if (check[num]) return false;
        check[num] = true;
    }
    // 세로줄 검사
    memset(check, 0, sizeof(check));
    check[n] = true;
    for (int i = 0; i < 9; i++) {
        int num = sudoku[i][c];
        if (!num) continue;
        if (check[num]) return false;
        check[num] = true;
    }
    // 3x3 정사각형 검사
    memset(check, 0, sizeof(check));
    check[n] = true;
    int startR, endR, startC, endC;
    if (r < 3) startR = 0, endR = 2;
    else if (r < 6) startR = 3, endR = 5;
    else if (r < 9) startR = 6, endR = 8;
    if (c < 3) startC = 0, endC = 2;
    else if (c < 6) startC = 3, endC = 5;
    else if (c < 9) startC = 6, endC = 8;
    for (int i = startR; i <= endR; i++) {
        for (int j = startC; j <= endC; j++) {
            int num = sudoku[i][j];
            if (!num) continue;
            if (check[num]) return false;
            check[num] = true;
        }
    }
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
            if (playSudoku(n + 1)) return true;
            sudoku[r][c] = 0;
        }
    }
    return false;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
            if (!sudoku[i][j]) blank.push_back({i, j});
        }
    }
sort(blank.begin(), blank.end());
    playSudoku(0);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
