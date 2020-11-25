#include <iostream>
#include <cstring>
#include <algorithm>
#define endl '\n'

using namespace std;

int n;
bool visited[101];
int matched[101];

// bipartite matching
bool dfs(int start, bool graph[][101], int maxTime) {
	for (int i = 0; i < maxTime; i++) {
		if (!graph[start][i] || visited[i]) continue;
		visited[i] = true;
		if (matched[i] == -1 || dfs(matched[i], graph, maxTime)) {
			matched[i] = start;
			return true;
		}
	}
	return false;
}

int main() {
	int t;
	cin >> t;

	while (t--) {
		int m;
		cin >> n >> m;

		int t1, t2, a;
		bool graph[101][101] {};
		int maxTime = -1;
		for (int i = 0; i < m; i++) {
			cin >> t1 >> t2 >> a;
			maxTime = max(maxTime, t2);

			int seed;
			for (int i = 0; i < a; i++) {
				cin >> seed;
				for (int t3 = t1; t3 < t2; t3++) {
					graph[seed][t3] = true;
				}
			}
		}

		memset(matched, -1, sizeof(matched));

		int count = 0;
		for (int i = 1; i <= n; i++) {
			count += dfs(i, graph, maxTime);
			memset(visited, 0, sizeof(visited));
		}

		if (count != n) {
			cout << -1 << endl;
			continue;
		}

		for (int i = 0; i < maxTime; i++) {
			if (matched[i] != -1) count = i;
		}

		cout << count + 1 << endl;
	}
	return 0;
}
