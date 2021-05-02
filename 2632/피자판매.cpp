#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;

	int m, n;
	cin >> m >> n;

	vector<int> a(m);
	for (int i = 0; i < m; i++) cin >> a[i];

	vector<int> aPrefix;
	for (int i = 0; i < m; i++) {
		int prefixSum = 0;
		for (int j = 0; j < m - 1; j++) {
			int idx = (i + j) % m;
			prefixSum += a[idx];
			aPrefix.push_back(prefixSum);
		}
		if (!i) aPrefix.push_back(prefixSum + a.back());
	}
	aPrefix.push_back(0);
	sort(aPrefix.begin(), aPrefix.end());

	vector<int> b(n);
	for (int i = 0; i < n; i++) cin >> b[i];

	vector<int> bPrefix;
	for (int i = 0; i < n; i++) {
		int prefixSum = 0;
		for (int j = 0; j < n - 1; j++) {
			int idx = (i + j) % n;
			prefixSum += b[idx];
			bPrefix.push_back(prefixSum);
		}
		if (!i) bPrefix.push_back(prefixSum + b.back());
	}
	bPrefix.push_back(0);
	sort(bPrefix.begin(), bPrefix.end());

	// 이분탐색 or 투포인터 가능
	long answer = 0;
	for (int i : aPrefix) {
		if (i > t) break;
		answer += upper_bound(bPrefix.begin(), bPrefix.end(), t - i) - lower_bound(bPrefix.begin(), bPrefix.end(), t - i);
	}

	cout << answer;
	
	return 0;
}
