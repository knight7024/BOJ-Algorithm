#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define endl '\n'

using namespace std;

struct coor
{
    int y;
    int x;
};

vector<coor> inci;
int firstCop[1002][1002];
int secondCop[1002][1002];
coor answer[1002][1002];
const int INF = 0x3f3f3f3f;

int getDistance(coor from, coor to)
{
    return abs(from.x - to.x) + abs(from.y - to.y);
}

void track(coor from)
{
    //base case
    if (!from.x && !from.y)
        return;

    coor to = answer[from.y][from.x];
    track(answer[from.y][from.x]);

    if (from.y > answer[from.y][from.x].y)
        cout << 1 << endl;
    else if (from.x > answer[from.y][from.x].x)
        cout << 2 << endl;
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    int W;
    cin >> W;

    // 초기화
    int dp[1002][1002];
    memset(dp, 0x3f, sizeof(dp));

    // 사건들의 좌표 저장
    inci.resize(W + 2);
    inci[0] = {1, 1};
    for (int i = 1; i <= W; i++)
    {
        cin >> inci[i].y >> inci[i].x;
    }
    inci[W + 1] = {N, N};

    // 경찰차들의 첫 좌표 설정
    firstCop[0][0] = 0;
    secondCop[0][0] = W + 1;
    dp[1][0] = getDistance(inci[firstCop[0][0]], inci[1]);
    firstCop[1][0] = 1;
    secondCop[1][0] = secondCop[0][0];
    dp[0][1] = getDistance(inci[secondCop[0][0]], inci[1]);
    secondCop[0][1] = 1;
    firstCop[0][1] = firstCop[0][0];

    int totalDistance = INF;
    coor totalCoor = {-1, -1};
    // 경찰차 1번
    for (int first = 0; first <= W; first++)
    {
        // 경찰차 2번
        for (int second = 0; second <= W; second++)
        {
            if (first == second)
                continue;

            //  다음 사건
            int nextW = max(first, second) + 1;

            // 경찰차 1번이 다음 사건으로 가는 거리
            int nextFirst = getDistance(inci[firstCop[first][second]], inci[nextW]);
            if (dp[nextW][second] > dp[first][second] + nextFirst)
            {
                dp[nextW][second] = dp[first][second] + nextFirst;
                firstCop[nextW][second] = nextW;
                secondCop[nextW][second] = secondCop[first][second];
                answer[nextW][second] = {first, second};
            }

            // 경찰차 2번이 다음 사건으로 가는 거리
            int nextSecond = getDistance(inci[secondCop[first][second]], inci[nextW]);
            if (dp[first][nextW] > dp[first][second] + nextSecond)
            {
                dp[first][nextW] = dp[first][second] + nextSecond;
                secondCop[first][nextW] = nextW;
                firstCop[first][nextW] = firstCop[first][second];
                answer[first][nextW] = {first, second};
            }
            if (first == W || second == W)
            {
                if (totalDistance > dp[first][second])
                {
                    totalDistance = dp[first][second];
                    totalCoor = {first, second};
                }
            }
        }
    }

    // 두 경찰차가 이동한 총 거리
    cout << totalDistance << endl;
    track(totalCoor);
    return 0;
}
