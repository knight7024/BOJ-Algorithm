#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

int n, m;
vector<int> chang;
bool dp[10][360];
bool check[360];

void dfs(int idx, int angle) {
	if (idx >= n) return;
	bool& ret = dp[idx][angle];
	if (ret) return;
	ret = check[angle] = true;

	dfs(idx, (angle + chang[idx]) % 360);
	dfs(idx, abs(angle - chang[idx]) % 360);
	dfs(idx + 1, angle);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	chang.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> chang[i];
	}

	vector<int> hyun(m);
	for (int i = 0; i < m; i++) {
		cin >> hyun[i];
	}
	
	dfs(0, 0);

	for (int i : hyun) {
		cout << (check[i] ? "YES" : "NO") << endl;
	}
	
	return 0;
}
