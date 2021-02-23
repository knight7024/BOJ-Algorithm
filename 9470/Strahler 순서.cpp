#include <iostream>
#include <queue>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--) {
		int k, m, p;
		cin >> k >> m >> p;

		vector<vector<int>> adj(m + 1);
		vector<vector<int>> adjRev(m + 1);
		vector<int> indegree(m + 1);
		for (int i = 0; i < p; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adjRev[b].push_back(a);
			indegree[b]++;
		}

		vector<int> strahler(m + 1);
		queue<int> topo;
		for (int i = 1; i <= m; i++) {
			if (indegree[i]) continue;
			topo.push(i);
			strahler[i] = 1;
		}

		vector<int> result;
		while (!topo.empty()) {
			int front = topo.front();
			topo.pop();
			result.push_back(front);

			for (int i : adj[front]) {
				if (--indegree[i]) continue;
				topo.push(i);
			}
		}

		int answer = 0;
		for (int node : result) {
			int maxStrahler = 1;
			int strahlerCount = 0;
			for (int i : adjRev[node]) {
				if (maxStrahler < strahler[i]) {
					maxStrahler = strahler[i];
					strahlerCount = 1;
				}
				else if (maxStrahler == strahler[i]) {
					strahlerCount++;
				}
			}
			strahler[node] = strahlerCount >= 2 ? maxStrahler + 1 : maxStrahler;
			answer = max(answer, strahler[node]);
		}

		cout << k << ' ' << answer << endl;
	}

	return 0;
}
