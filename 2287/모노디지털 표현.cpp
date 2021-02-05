#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

int getSameNumber(int k, int digit) {
	int result = 0;
	for (int i = 0; i < digit; i++) {
		result = result * 10 + 1;
	}

	return result * k;
}

int main() {
	int k, n;
	cin >> k >> n;

	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;

		int answer = -1;
		vector<unordered_set<int>> adj(8);
		for (int x = 1; x <= 8; x++) {
			adj[x - 1].insert(getSameNumber(k, x));
			for (int y = 1; y < x; y++) {
				int z = x - y;
				for (int a : adj[y - 1]) {
					for (int b : adj[z - 1]) {
						adj[x - 1].insert(a + b);
						adj[x - 1].insert(a - b);
						if (b) adj[x - 1].insert(a / b);
						adj[x - 1].insert(a * b);
					}
				}
			}
			if (adj[x - 1].find(num) != adj[x - 1].end()) {
				answer = x;
				break;
			}
		}

		if (answer == -1) cout << "NO" << endl;
		else cout << answer << endl;
	}

	return 0;
}
