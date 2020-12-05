#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	int graph[401][401] {};
	for (int i = 0; i < k; i++) {
		int s1, s2;
		cin >> s1 >> s2;
		graph[s1][s2] = -1;
		graph[s2][s1] = 1;
	}

	// b 정점을 거쳐서
	for (int b = 1; b <= n; b++) {
		// a 정점에서
		for (int a = 1; a <= n; a++) {
			// c 정점으로 가는 최단 거리
			for (int c = 1; c <= n; c++) {
				// a에서 b가 연결되어 있고, b에서 c가 연결되어 있으면
				if (graph[a][b] == -1 && graph[b][c] == -1) {
					graph[a][c] = -1;
					graph[c][a] = 1;
				}
			}
		}
	}

	int s;
	cin >> s;

	while (s--) {
		int s1, s2;
		cin >> s1 >> s2;
		cout << graph[s1][s2] << endl;
	}
	return 0;
}
