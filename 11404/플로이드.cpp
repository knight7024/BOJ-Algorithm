#include <iostream>
#include <cstring>
#define endl '\n'

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;

	int m;
	cin >> m;

	int graph[101][101];
	memset(graph, 0x3f, sizeof(graph));

	int from, to, cost;
	for (int i = 0; i < m; i++) {
		cin >> from >> to >> cost;
		graph[from][to] = min(graph[from][to], cost);
	}

	// j를 거쳐서
	for (int j = 1; j <= n; j++) {
		// i를 통해
		for (int i = 1; i <= n; i++) {
			// k로 가는 최소 비용
			for (int k = 1; k <= n; k++) {
				if (i == j || j == k || i == k) continue;
				if (graph[i][j] != INF && graph[j][k] != INF) {
					graph[i][k] = min(graph[i][k], graph[i][j] + graph[j][k]);
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << (i == j || graph[i][j] == INF ? 0 : graph[i][j]) << " ";
		}
		cout << endl;
	}
	return 0;
}
