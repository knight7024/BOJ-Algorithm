#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define endl '\n'
using namespace std;

struct Coor {
    int y;
    int x;
};

const int INF = 0x3f3f3f3f;

int n, w;
vector<Coor> inci;
// [A][B]: 경찰차 1이 A번째 사건에 있고 경찰차 2가 B번째 사건에 있을 때 최소 이동거리
int dp[1001][1001];

int getDistance(Coor from, Coor to) {
	return abs(from.x - to.x) + abs(from.y - to.y);
}

void track(int cop1, int cop2) {
	if (cop1 == w || cop2 == w) return;

	int nowDist = dp[cop1][cop2];

	int nextInci = max(cop1, cop2) + 1;
	int cop1Dist = cop1 ? getDistance(inci[cop1], inci[nextInci]) : getDistance({1, 1}, inci[nextInci]);
	int cop2Dist = cop2 ? getDistance(inci[cop2], inci[nextInci]) : getDistance({n, n}, inci[nextInci]);

	if (dp[cop1][nextInci] == nowDist - cop2Dist) {
		cout << 2 << endl;
		track(cop1, nextInci);
	}
	else if (dp[nextInci][cop2] == nowDist - cop1Dist) {
		cout << 1 << endl;
		track(nextInci, cop2);
	}
}

int dfs(int cop1, int cop2) {
	int& ret = dp[cop1][cop2];
	if (cop1 == w || cop2 == w) return ret = 0;
	if (ret != INF) return ret;

	int nextInci = max(cop1, cop2) + 1;
	int cop1Dist = cop1 ? getDistance(inci[cop1], inci[nextInci]) : getDistance({1, 1}, inci[nextInci]);
	int cop2Dist = cop2 ? getDistance(inci[cop2], inci[nextInci]) : getDistance({n, n}, inci[nextInci]);

	return ret = min(dfs(nextInci, cop2) + cop1Dist, dfs(cop1, nextInci) + cop2Dist);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> w;

	inci.resize(w + 1);
	for (int i = 1; i <= w; i++) {
		cin >> inci[i].y >> inci[i].x;
	}

	memset(dp, INF, sizeof(dp));

	cout << dfs(0, 0) << endl;

	track(0, 0);

	return 0;
}
