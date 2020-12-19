#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define FIRSTCITY 0
#define MAXCITY 16
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
int cost[MAXCITY][MAXCITY];
// [A][B]: A번 마을에서 다른 마을들을 가봤을 때의 최소 비용
// ex) [1][0111]: 1번 마을에서 0번, 2번 마을을 가봤을 때 최소 비용
int dp[MAXCITY][1 << MAXCITY];

int dfs(int nowNode, int bitDp) {
	int& ret = dp[nowNode][bitDp];
	// 이미 저장된 도시라면 그대로 반환
	if (ret != INF) return ret;
	// N개의 도시를 모두 거치고 처음으로 돌아오는 길이 있다면
	if (bitDp == (1 << n) - 1 && cost[nowNode][FIRSTCITY]) {
		return ret = cost[nowNode][FIRSTCITY];
	}

	int result = INF;
	// N개의 도시를 거치기 전까진 돌아가면 안되므로 1번부터 탐색
	for (int i = 1; i < n; i++) {
		// 연결된 길이 있다면
		if (!(bitDp & 1 << i) && cost[nowNode][i]) {
			result = min(result, dfs(i, bitDp | (1 << i)) + cost[nowNode][i]);
		}
	}

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> cost[i][j];
		}
	}

	memset(dp, INF, sizeof(dp));

	cout << dfs(FIRSTCITY, 1);

	return 0;
}
