#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	long x;
	while (cin >> x) {
		int n;
		cin >> n;

		vector<long> lego(n);
		for (int i = 0; i < n; i++) {
			cin >> lego[i];
		}

		sort(lego.begin(), lego.end());

		bool flag = false;
		for (auto it = lego.begin(); it != lego.end(); it++) {
			auto target = lower_bound(next(it), lego.end(), abs(x * 1e7 - *it));
			if (next(it) == lego.end() || *it + *target != x * 1e7) continue;
			cout << "yes " << *it << ' ' << *target << endl;
			flag = true;
			break;
		}

		if (!flag) cout << "danger" << endl;
	}

	return 0;
}
