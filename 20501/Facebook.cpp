#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

const int SIZE = 32;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	int bit[2000][63] {};
	for (int i = 0; i < n; i++) {
		char str[2001];
		cin >> str;
		for (int j = 0; str[j]; j++) {
			bit[i][j / SIZE] |= ((str[j] == '1') << (n - (j % SIZE) - 1));
		}
	}

	int q;
	cin >> q;

	while (q--) {
		int a, b;
		cin >> a >> b;

		int answer = 0;
		for (int i = 0; i < 63; i++) {
			answer += __builtin_popcount(bit[a - 1][i] & bit[b - 1][i]);
		}
		cout << answer << '\n';
	}
}
