#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;
bool visited[1001];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    
	int M;
	cin >> N >> M;

	vector<vector<int>> adj(N + 1);
	int u, v;
	for (int i = 0; i < M; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int answer = 0;
	queue<int> q;
	for (int i = 1; i <= N; i++) {
		if (visited[i]) continue;

		q.push(i);
		++answer;
		while (!q.empty()) {
			int front = q.front();
			visited[front] = true;
			q.pop();
			for (int j = 0; j < adj[front].size(); j++) {
				if (!visited[adj[front][j]]) {
					q.push(adj[front][j]);
					visited[adj[front][j]] = true;
				}
			}
		}
	}
	cout << answer;
}
