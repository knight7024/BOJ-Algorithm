#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> wine;
int dp[10001][3];

int dfs(int idx, int rest) {
	int& ret = dp[idx][rest];
	if (idx == n - 1) return ret = wine[idx];
	if (ret) return ret;

	int result = 0;
	if (rest + 1 < 3) {
		result = max(result, dfs(idx + 1, rest + 1));
	}
	for (int i = idx + 2; i < n; i++) {
		result = max(result, dfs(i, 1));
	}

	return ret = result + wine[idx];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	wine.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> wine[i];
	}

	int answer = 0;
	for (int i = 0; i < n; i++) {
		answer = max(answer, dfs(i, 1));
	}

	cout << answer;
}
