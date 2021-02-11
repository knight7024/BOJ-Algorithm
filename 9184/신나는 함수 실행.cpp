#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long dp[51][51][51];

long dfs(int a, int b, int c) {
	if (a <= 0 || b <= 0 || c <= 0) return 1;
	if (a > 20 || b > 20 || c > 20) return dfs(20, 20, 20);
	long& ret = dp[a][b][c];
	if (ret != -1) return ret;

	if (a < b && b < c) return ret = dfs(a, b, c - 1) + dfs(a, b - 1, c - 1) - dfs(a, b - 1, c);
	else return ret = dfs(a - 1, b, c) + dfs(a - 1, b - 1, c) + dfs(a - 1, b, c - 1) - dfs(a - 1, b - 1, c - 1);
	return ret;
}

int main() {
	int a, b, c;
	
	memset(dp, -1, sizeof(dp));
	while (1) {
		scanf("%d%d%d", &a, &b, &c);
		if (a == -1 && b == -1 && c == -1) break;
		printf("w(%d, %d, %d) = %ld\n", a, b, c, dfs(a, b, c));
	}

	return 0;
}
