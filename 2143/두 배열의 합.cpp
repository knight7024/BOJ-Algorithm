#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	int n;
	cin >> n;

	LL nArray[1001];
	LL nPrefix[1002];
	nPrefix[0] = 0;
	for (int i = 0; i < n; i++) {
		cin >> nArray[i];
		nPrefix[i + 1] = nArray[i] + nPrefix[i];
	}

	int m;
	cin >> m;

	LL mArray[1001];
	LL mPrefix[1002];
	mPrefix[0] = 0;
	for (int i = 0; i < m; i++) {
		cin >> mArray[i];
		mPrefix[i + 1] = mArray[i] + mPrefix[i];
	}

	vector<LL> nPrefixComb;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			nPrefixComb.emplace_back(nPrefix[i] - nPrefix[j]);
		}
	}

	sort(nPrefixComb.begin(), nPrefixComb.end());

	vector<LL> mPrefixComb;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < i; j++) {
			mPrefixComb.emplace_back(mPrefix[i] - mPrefix[j]);
		}
	}

	sort(mPrefixComb.begin(), mPrefixComb.end());

	LL answer = 0;
	for (LL i : nPrefixComb) {
		auto start = lower_bound(mPrefixComb.begin(), mPrefixComb.end(), t - i);
		auto end = upper_bound(mPrefixComb.begin(), mPrefixComb.end(), t - i);
		answer += distance(start, end);
	}

	cout << answer;

	return 0;
}
