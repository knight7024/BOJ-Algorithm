#include <iostream>
#include <cstring>
using namespace std;

int n;
int city[1000][1000];
int dp[1000][1000][3];

int dfs(int r, int c, int lastMilk) {
	bool milkFlag = city[r][c] == (lastMilk + 1) % 3;
	if (r == n - 1 && c == n - 1) return milkFlag;
	int& ret = dp[r][c][lastMilk];
	if (ret != -1) return ret;

	ret = 0;
	if (r + 1 < n) ret = max(ret, dfs(r + 1, c, milkFlag ? city[r][c] : lastMilk) + milkFlag);
	if (c + 1 < n) ret = max(ret, dfs(r, c + 1, milkFlag ? city[r][c] : lastMilk) + milkFlag);

	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> city[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));

	cout << dfs(0, 0, 2);

	return 0;
}
