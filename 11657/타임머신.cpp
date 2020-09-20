#include <iostream>
#include <cstring>
#include <vector>
#define endl '\n'

using namespace std;

const int INF = 987654321;

struct node {
	int next;
	int weight;
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<node>> adj(n + 1);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		adj[a].push_back({b, c});
	}

	long dst[501];
	memset(dst, INF, sizeof(dst));
	dst[1] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (auto& node : adj[j]) {
				int next = node.next;
				int weight = node.weight;

				if (dst[j] != INF && dst[next] > dst[j] + weight) {
					dst[next] = dst[j] + weight;
					if (i == n) {
						cout << -1;
						exit(0);
					}
				}
			}
		}
	}

	for (int i = 2; i <= n; i++)
		cout << (dst[i] == INF ? -1 : dst[i]) << endl;
	return 0;
}
