#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX 2147483647
#define endl '\n'
using namespace std;

vector<int> book;
int dp[501][501];
int prefixSum[501];

int dfs(int from, int to) {
	if (from == to) return 0;
	int& ret = dp[from][to];
	if (ret != -1) return ret;

	int result = MAX;
	for (int i = from; i < to; i++) {
		int sumCost = dfs(from, i) + dfs(i + 1, to);
		result = min(result, sumCost + prefixSum[to + 1] - prefixSum[from]);
	}

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--) {
		int k;
		cin >> k;

		memset(prefixSum, 0, sizeof(prefixSum));
		book.clear(); book.resize(k);
		prefixSum[0] = 0;
		for (int i = 0; i < k; i++) {
			cin >> book[i];
			prefixSum[i + 1] = book[i] + prefixSum[i];
		}

		memset(dp, -1, sizeof(dp));

		cout << dfs(0, k - 1) << endl;
	}
	return 0;
}
