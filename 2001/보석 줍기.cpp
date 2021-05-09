#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int hasJewelry[101];
vector<vector<pair<int, int>>> adj;
bool visited[101][1 << 14];
int answer;

void dfs(int node, int state) {
	visited[node][state] = true;
	int nowJewelry = __builtin_popcount(state);
	if (!node) answer = max(answer, nowJewelry);

	for (auto& it : adj[node]) {
		// 보석을 줍고 가는 경우
		if (hasJewelry[node]) {
			int jewelryState = 1 << (hasJewelry[node] - 1);
			if (!visited[it.first][state | jewelryState] && !(state & jewelryState) && it.second >= nowJewelry + 1) {
				dfs(it.first, state | jewelryState);
			}
		}
		// 보석을 줍지 않고 가는 경우
		if (!visited[it.first][state] && it.second >= nowJewelry) {
			dfs(it.first, state);
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 0; i < k; i++) {
		int island;
		cin >> island;
		hasJewelry[island] = i + 1;
	}

	adj.resize(n + 1);
	adj[0].emplace_back(1, 100);
	adj[1].emplace_back(0, 100);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].emplace_back(b, c);
		adj[b].emplace_back(a, c);
	}

	dfs(0, 0);

	cout << answer;

	return 0;
}
