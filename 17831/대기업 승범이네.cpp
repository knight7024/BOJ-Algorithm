#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> ability;
int dp[200001][2];

int dfs(int person, bool isMentor) {
	if (adj[person].empty()) return 0;
	int& ret = dp[person][isMentor];
	if (ret != -1) return ret;

	// 한 판매원은 최대 1개의 멘토링 관계에만 속할 수 있다.
	ret = 0;
	// 본인이 멘토라면
	if (isMentor) {
		// 본인과 가장 시너지가 최대인 멘티를 찾는다.
		int maxResult = 0;
		for (int child : adj[person]) {
			maxResult += max(dfs(child, 0), dfs(child, 1));
		}

		for (int child : adj[person]) {
			ret = max(ret, maxResult - max(dfs(child, 0), dfs(child, 1)) + dfs(child, 0) + ability[person] * ability[child]);
		}
	}
	// 본인이 멘토가 아니라면
	else {
		// 전혀 상관 없으니 그냥 최대 시너지를 찾는다.
		for (int child : adj[person]) {
			ret += max(dfs(child, 0), dfs(child, 1));
		}
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	adj.resize(n + 1);
	for (int i = 2; i <= n; i++) {
		int mentor;
		cin >> mentor;
		adj[mentor].push_back(i);
	}

	ability.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> ability[i];
	}

	memset(dp, -1, sizeof(dp));

	cout << max(dfs(1, 0), dfs(1, 1));

	return 0;
}
