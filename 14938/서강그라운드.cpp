#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, r;
	cin >> n >> m >> r;

	vector<int> items(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> items[i];
	}

	int dist[101][101];
	memset(dist, INF, sizeof(dist));

	for (int i = 0; i < r; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		dist[a][b] = dist[b][a] = l;
	}

	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= n; i++) {
			for (int k = 1; k <= n; k++) {
				if (dist[i][j] && dist[j][k]) {
					if (i == j || i == k || j == k) continue;
					dist[i][k] = min(dist[i][k], dist[i][j] + dist[j][k]);
				}
			}
		}
	}

	int answer = 0;
	for (int i = 1; i <= n; i++) {
		int getItem = 0;
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] > m || dist[i][j] == INF) continue;
			getItem += items[j];
		}
		answer = max(answer, getItem + items[i]);
	}

	cout << answer;

	return 0;
}
