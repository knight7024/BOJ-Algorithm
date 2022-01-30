#include <bits/stdc++.h>
#define MAX 64
using namespace std;

const int dy[5][4][4] {
    {
        {-1, },
        {0, },
        {1, },
        {0, }
    },
    {
        {-1, 1},
        {0, 0},
        {1, -1},
        {0, 0}
    },
    {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    },
    {
        {0, -1, 0},
        {-1, 0, 1},
        {0, 1, 0},
        {1, 0, -1}
    },
    {
        {-1, 0, 1, 0},
        {-1, 0, 1, 0},
        {-1, 0, 1, 0},
        {-1, 0, 1, 0}
    }
};

const int dx[5][4][4] {
    {
        {0, },
        {1, },
        {0, },
        {-1, }
    },
    {
        {0, 0},
        {-1, 1},
        {0, 0},
        {-1, 1}
    },
    {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0}
    },
    {
        {-1, 0, 1},
        {0, 1, 0},
        {-1, 0, 1},
        {0, -1, 0}
    },
    {
        {0, 1, 0, -1},
        {0, 1, 0, -1},
        {0, 1, 0, -1},
        {0, 1, 0, -1}
    }
};

struct Coor {
    int y, x;
    Coor() {}
    Coor(int y, int x): y(y), x(x) {}
};

int n, m;
int office[8][8];
int officeSum[8][8];
vector<Coor> cctv;
// CCTV가 바라보고 있는 방향 (0: 위, 1: 오른쪽, 2: 아래, 3: 왼쪽)
vector<int> cctvDirs;
int answer = MAX;

int getCCTV(Coor& a) {
    return office[a.y][a.x];
}

int findBlindSpot() {
    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ret += officeSum[i][j] == 0;
        }
    }
    return ret;
}

void fillMap(int pos, int mult) {
    int cctvType = getCCTV(cctv[pos]) - 1;
    for (int d = 0; d < 4; d++) {
        if (!dy[cctvType][cctvDirs[pos]][d] and !dx[cctvType][cctvDirs[pos]][d]) break;
        int y = cctv[pos].y, x = cctv[pos].x;
        while (1) {
            y += dy[cctvType][cctvDirs[pos]][d]; x += dx[cctvType][cctvDirs[pos]][d];
            if (y < 0 or y >= n or x < 0 or x >= m or office[y][x] == 6) break;
            if (office[y][x] > 0) continue;
            officeSum[y][x] += (cctvType + 1) * mult;
        }
    }
}

void backtracking(int pos) {
    if (pos == cctv.size()) {
        answer = min(answer, findBlindSpot());
        return;
    }

    for (int i = 0; i < 4; i++) {
        cctvDirs.push_back(i);
        fillMap(pos, 1);
        backtracking(pos + 1);
        fillMap(pos, -1);
        cctvDirs.pop_back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> office[i][j];
            officeSum[i][j] = office[i][j] ? -1 : 0;
            if (office[i][j] > 0 and office[i][j] < 6) cctv.emplace_back(i, j);
        }
    }

    backtracking(0);

    cout << answer;

    return 0;
}
