#include <bits/stdc++.h>
using namespace std;

int n, m;
char board[16][16];

int getMaxSize(int y, int x) {
    int size = 1;
    while (1) {
        for (int i = y - size; i <= y + size; i++) if (i < 0 || i >= n || board[i][x] != '#') return size - 1;
        for (int i = x - size; i <= x + size; i++) if (i < 0 || i >= m || board[y][i] != '#') return size - 1;
        size++;
    }
    return size - 1;
}

void setCross(int y, int x, int size, char target) {
    for (int i = y - size; i <= y + size; i++) board[i][x] = target;
    for (int i = x - size; i <= x + size; i++) board[y][i] = target;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n >> m;

    vector<pair<int, int>> blank;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (board[i][j] == '#') blank.emplace_back(i, j);
        }
    }

    int answer = 0;
    for (int i = 0; i < blank.size() - 1; i++) {
        int size1 = getMaxSize(blank[i].first, blank[i].second);
        for (int s1 = 0; s1 <= size1; s1++) {
            setCross(blank[i].first, blank[i].second, s1, '*');
            for (int j = i + 1; j < blank.size(); j++) {
                if (board[blank[j].first][blank[j].second] != '#') continue;
                int size2 = getMaxSize(blank[j].first, blank[j].second);
                answer = max(answer, (s1 * 4 + 1) * (size2 * 4 + 1));
            }
        }
        setCross(blank[i].first, blank[i].second, size1, '#');
    }

    cout << answer;

    return 0;
}
