#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

int n, m, h;
// [A][B]: A번째 세로선에서 A+1번째 세로선으로 B번째 위치에서 이동 가능 여부
bool ladder[11][31];
int answer = INF;

bool isSuccess() {
    for (int i = 1; i <= n; i++) {
        int c = i;
        for (int r = 1; r <= h; r++) {
            if (c + 1 <= n and ladder[c][r]) c++;
            else if (c - 1 >= 1 and ladder[c - 1][r]) c--;
        }
        if (c != i) return false;
    }
    return true;
}

void backtracking(int line, int depth, int connect) {
    if (isSuccess()) {
        answer = min(answer, connect);
        return;
    }

    if (connect < 3) {
        for (int c = line; c < n; c++) {
            for (int r = depth; r <= h; r++) {
                if (ladder[c][r] or ladder[c - 1][r] or ladder[c + 1][r]) continue;
                ladder[c][r] = true;
                backtracking(c, r + 1, connect + 1);
                ladder[c][r] = false;
            }
            depth = 1;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> h;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        ladder[b][a] = true;
    }

    backtracking(1, 1, 0);

    cout << (answer == INF ? -1 : answer);

    return 0;
}
