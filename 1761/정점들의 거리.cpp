#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 17
#define endl '\n'

using namespace std;

int n;
int ancestor[40001][MAX];
// [to][from][dis]
vector<vector<pair<int, int>>> adj;
int depth[40001];
int visited[40001];

void dfs(int start, int d, int dist) {
	visited[start] = dist;
	depth[start] = d;

	for (int i = 0; i < adj[start].size(); i++) {
		int next = adj[start][i].first;
		int nextDis = adj[start][i].second;
		if (!visited[next]) {
			ancestor[next][0] = start;
			dfs(next, d + 1, dist + nextDis);
		}
	}
}

void dp() {
	for (int j = 1; j < MAX; j++) {
		for (int i = 1; i <= n; i++) {
			ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
		}
	}
}

int lca(int x, int y) {
	int dist = 0;
	// 항상 x가 더 깊은 노드로 맞춰준다.
	if (depth[x] < depth[y]) swap(x, y);

	// 더 깊은 노드를 최대한 위로 끌어올린다.
	for (int i = MAX - 1; i >= 0; i--) {
		if (depth[x] - depth[y] >= (1 << i)) {
			dist += visited[x] - visited[ancestor[x][i]];
			x = ancestor[x][i];
		}
	}
	if (x == y) return dist;

	for (int j = MAX - 1; j >= 0; j--) {
		if (ancestor[x][j] != ancestor[y][j]) {
			dist += visited[x] - visited[ancestor[x][j]];
			x = ancestor[x][j];
			dist += visited[y] - visited[ancestor[y][j]];
			y = ancestor[y][j];
		}
	}
	return dist + (visited[x] - visited[ancestor[x][0]]) + (visited[y] - visited[ancestor[y][0]]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
	cin >> n;
	adj.resize(n + 1);

	int to, from, dis;
	for (int i = 1; i < n; i++) {
		cin >> to >> from >> dis;
		adj[to].push_back({from, dis});
		adj[from].push_back({to, dis});
	}

	// 어디가 루트이던 상관 없으니 1을 루트로 가정한다.
	dfs(1, 0, 0);
	dp();

	int m;
	cin >> m;

	int x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		cout << lca(x, y) << endl;
	}
	return 0;
}
