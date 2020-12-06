#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	bool graph[501][501] {};
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		graph[a][b] = true;
	}

	// j를 거쳐서
	for (int j = 1; j <= n; j++) {
		// i에서
		for (int i = 1; i <= n; i++) {
			// k로
			for (int k = 1; k <= n; k++) {
				if (graph[i][j] && graph[j][k]) {
					graph[i][k] = true;
				}
			}
		}
	}

	int answer = 0;
	for (int i = 1; i <= n; i++) {
		int bigger = 0;
		for (int j = 1; j <= n; j++) {
			bigger += graph[i][j];
		}

		int smaller = 0;
		for (int j = 1; j <= n; j++) {
			smaller += graph[j][i];
		}

		answer += bigger + smaller == n - 1;
	}

	cout << answer;
	return 0;
}
