#include <iostream>
#include <vector>
#include <algorithm>
#define INF 987654321
using namespace std;

struct coor {
    int y;
    int x;
    bool operator == (coor a) {
        return x == a.x && y == a.y;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int r, c;
    cin >> r >> c;

    coor start {};
    coor end {r - 1, c - 1};

    int map[1001][1001];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> map[i][j];
        }
    }

    // 높이가 홀수라면
    // →↓←↓→ 반복
    if (r % 2) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c - 1; j++) {
                cout << (i % 2 ? 'L' : 'R');
            }
            if (i != r - 1) cout << 'D';
        }
    }
    // 너비가 홀수라면
    // ↓→↑→↓ 반복
    else if (c % 2) {
        for (int i = 0; i < c; i++) {
            for (int j = 0; j < r - 1; j++) {
                cout << (i % 2 ? 'U' : 'D');
            }
            if (i != c - 1) cout << 'R';
        }
    }
    // 둘 중 하나 이상이 홀수면 뭘 해도 상관 없다.
    // 문제는 둘 다 짝수인 경우
    else {
        int minHappiness = INF;
        coor minCoor;

        // 갈 수 없는 곳 중 행복이 최소인 값 찾는다.
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if ((i + j) % 2 && minHappiness > map[i][j]) {
                    minHappiness = map[i][j];
                    minCoor = {i, j};
                }
            }
        }

        // 현재 위치 (default: 0, 0)
        coor now {};

        // 그리디 + 구현
        string result;

        // 최소의 행복 위치 바로 전까지 이동한다.
        // ↓→↑→↓ 반복
        for (int i = 0; i < minCoor.x - 1; i++) {
            for (int j = 0; j < r - 1; j++) {
                result += i % 2 ? 'U' : 'D';
                i % 2 ? now.y-- : now.y++;
            }
            result += 'R', now.x++;
        }

        // 이동을 멈춘 곳이 맨 위라면
        if (!now.y) {
            // →↓←↓→ 반복
            bool flag = 0;
            while (now.y < r - 1) {
                if (now.y == minCoor.y) {
                    if (now.y == r - 1) {
                        if (now.x < c - 1) result += 'R', now.x++;
                        break;
                    }
                    result += 'D', now.y++;
                    continue;
                }
                result += flag % 2 ? 'L' : 'R';
                flag % 2 ? now.x-- : now.x++;
                if (now.y < r - 1) result += 'D', now.y++;
                flag ^= 1;
            }
            result += 'R', now.x++;
            // 아직 끝나지 않았으면 오른쪽으로 이동
            if (now.x < c - 1) result += 'R', now.x++;

            // 나머지도 자연스럽게 이동한다.
            // ↑→↓→↑ 반복
            flag = 0;
            while (1) {
                if (now == end) break;
                for (int j = 0; j < r - 1; j++) {
                    result += flag % 2 ? 'D' : 'U';
                    flag % 2 ? now.y++ : now.y--;
                }
                if (now == end) break;
                result += 'R', now.x++;
                flag ^= 1;
            }
        }
        // 이동을 멈춘 곳이 맨 아래라면
        else if (now.y == r - 1) {
            // →↑←↑→ 반복
            bool flag = 0;
            while (now.y > 0) {
                if (now.y == minCoor.y) {
                    if (!now.y) {
                        if (now.x < c - 1) result += 'R', now.x++;
                        break;
                    }
                    result += 'U', now.y--;
                    continue;
                }
                result += flag % 2 ? 'L' : 'R';
                flag % 2 ? now.x-- : now.x++;
                if (now.y > 0) result += 'U', now.y--;
                flag ^= 1;
            }
            result += 'R', now.x++;
            // 아직 끝나지 않았으면 오른쪽으로 이동
            if (now.x < c - 1) result += 'R', now.x++;

            // 나머지도 자연스럽게 이동한다.
            // ↓→↑→↓ 반복
            flag = 0;
            while (1) {
                if (now == end) break;
                for (int j = 0; j < r - 1; j++) {
                    result += flag % 2 ? 'U' : 'D';
                    flag % 2 ? now.y-- : now.y++;
                }
                if (now == end) break;
                result += 'R', now.x++;
                flag ^= 1;
            }
        }

        cout << result;
    }

    return 0;
}
