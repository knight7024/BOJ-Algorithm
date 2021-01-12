#include <iostream>
#include <cstring>
#include <algorithm>
#define endl '\n'
using namespace std;

int n, m;
int score[11];
// [A]][B]: 팔굽혀펴기의 누적 횟수가 A인데 현재 팀의 점수가 B일 때 득점한 최대 점수
int dp[1100][5001];

int dfs(int prefixSum, int nowScore) {
	if (nowScore == n) return prefixSum;
	int& ret = dp[prefixSum][nowScore];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < m; i++) {
		if (prefixSum + score[i] + nowScore > n) continue;
		ret = max(ret, dfs(prefixSum + score[i], prefixSum + score[i] + nowScore));
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--) {
		cin >> n >> m;

		for (int i = 0; i < m; i++) {
			cin >> score[i];
		}

		memset(dp, -1, sizeof(dp));

		int result = dfs(0, 0);
		cout << (result ? result : -1) << endl;
	}
	return 0;
}
