#include <iostream>
#define MOD 1000000000
using namespace std;

int n;
// [A][B][C]: A번째 숫자가 B인데 C 상태를 가지고 있을 때 계단 수의 개수
int dp[101][10][1 << 10];

int dfs(int idx, int num, int state) {
	// base case: 계단 수를 모두 채웠을 때
	if (idx == n) return state == (1 << 10) - 1;
	int& ret = dp[idx][num][state];
	if (ret) return ret;

	int result = 0;
	// 이전 숫자가 0이면 1로만 갈 수 있다.
	if (!num) result += dfs(idx + 1, 1, state | 1 << 1) % MOD;
	// 이전 숫자가 9면 8로만 갈 수 있다.
	else if (num == 9) result += dfs(idx + 1, 8, state | 1 << 8) % MOD;
	// 아니라면 -1, +1 모두 갈 수 있다.
	else {
		result = (result % MOD + dfs(idx + 1, num - 1, state | 1 << (num - 1)) % MOD) % MOD;
		result = (result % MOD + dfs(idx + 1, num + 1, state | 1 << (num + 1)) % MOD) % MOD;
	}

	return ret = result % MOD;
}

int main() {
	cin >> n;

	if (n < 10) cout << 0, exit(0);
	else if (n == 10) cout << 1, exit(0);

	int answer = 0;
	for (int i = 1; i <= 9; i++) {
		answer = (answer % MOD + dfs(1, i, 1 << i) % MOD) % MOD;
	}

	cout << answer;

	return 0;
}
