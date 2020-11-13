#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;

	vector<int> train(n + 1);
	for (int i = 1; i <= m; i++) {
		int type, order, seat;
		cin >> type >> order;

		switch (type) {
		case 1:
			cin >> seat;
			train[order] |= (1 << (seat - 1));
			break;
		case 2:
			cin >> seat;
			train[order] &= (((1 << 20) - 1) ^ (1 << (seat - 1)));
			break;
		case 3:
			train[order] = (train[order] << 1) & ((1 << 20) - 1);
			break;
		case 4:
			train[order] >>= 1;
			break;
		}
	}
	
	unordered_set<int> milky;
	for (int i = 1; i <= n; i++) {
		milky.insert(train[i]);
	}
	
	cout << milky.size();
	return 0;
}
