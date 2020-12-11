#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

// 방향 이동에 따른 힘
int power[5][5] = {
	{0, 2, 2, 2, 2},
	{0, 1, 3, 4, 3},
	{0, 3, 1, 3, 4},
	{0, 4, 3, 1, 3},
	{0, 3, 4, 3, 1}
};

// [N][L][R]: N번째까지 왔을 때 (L, R) 의 최솟값
int dp[100001][5][5];
vector<int> ddr;

int dfs(int idx, int L, int R) {
	if (idx == ddr.size() - 1) return 0;
	int& ret = dp[idx][L][R];
	if (ret != -1) return ret;

	int nextStep = ddr[idx];
	int result = INF;
	result = dfs(idx + 1, nextStep, R) + power[L][nextStep];
	result = min(result, dfs(idx + 1, L, nextStep) + power[R][nextStep]);

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int dir = -1;
	while (dir) {
		cin >> dir;
		ddr.push_back(dir);
	}

	memset(dp, -1, sizeof(dp));

	cout << dfs(0, 0, 0);

	return 0;
}
