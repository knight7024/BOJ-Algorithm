#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<long> a(n), b(n), c(n), d(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	}

	vector<long> ab, cd;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ab.push_back(a[i] + b[j]);
			cd.push_back(c[i] + d[j]);
		}
	}

	sort(ab.begin(), ab.end());
	sort(cd.begin(), cd.end());

	long answer = 0;
	for (long i : ab) {
		auto from = lower_bound(cd.begin(), cd.end(), -i);
		auto to = upper_bound(cd.begin(), cd.end(), -i);
		answer += distance(from, to);
	}

	cout << answer;

	return 0;
}
