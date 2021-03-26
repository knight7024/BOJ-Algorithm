#include <iostream>
#include <cstring>
using namespace std;

int n;
int price[16][16];
int dp[1 << 15][16][10];

int dfs(int bit, int to, int beforePrice) {
	int& ret = dp[bit][to][beforePrice];
	if (ret != -1) return ret;
	
	ret = 1;
	for (int i = 1; i <= n; i++) {
		// 1. 그림을 팔 때, 그림을 산 가격보다 크거나 같은 가격으로 팔아야 한다.
		if (price[to][i] < beforePrice) continue;
		// 2. 같은 그림을 두 번 이상 사는 것은 불가능하다.
		if (bit & 1 << (i - 1)) continue;
		ret = max(ret, dfs(bit | 1 << (i - 1), i, price[to][i]) + 1);
	}
	
	return ret;
}

int main() {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			char c;
			cin >> c;
			price[i][j] = c - '0';
		}
	}
	
	memset(dp, -1, sizeof(dp));
	
	cout << dfs(1, 1, 0);
	
	return 0;
}
