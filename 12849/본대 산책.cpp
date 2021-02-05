#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAXPOS 8
#define MAXD 100000
using namespace std;

const int MOD = 1e9 + 7;

int d;
vector<int> adj[MAXPOS];
int dp[8][MAXD + 1];

int dfs(int pos, int time) {
	if (time == d) return pos == 0;
	int& ret = dp[pos][time];
	if (ret != -1) return ret;

	int result = 0;
	for (int i : adj[pos]) {
		result = (result + dfs(i, time + 1)) % MOD;
	}

	return ret = result;
}

int main() {
	cin >> d;

	adj[0].push_back(1); adj[1].push_back(0);
	adj[0].push_back(2); adj[2].push_back(0);
	adj[2].push_back(3); adj[3].push_back(2);
	adj[1].push_back(3); adj[3].push_back(1);
	adj[1].push_back(2); adj[2].push_back(1);
	adj[3].push_back(4); adj[4].push_back(3);
	adj[3].push_back(5); adj[5].push_back(3);
	adj[4].push_back(5); adj[5].push_back(4);
	adj[4].push_back(6); adj[6].push_back(4);
	adj[2].push_back(4); adj[4].push_back(2);
	adj[5].push_back(7); adj[7].push_back(5);
	adj[6].push_back(7); adj[7].push_back(6);


	memset(dp, -1, sizeof(dp));

	cout << dfs(0, 0);

	return 0;
}
