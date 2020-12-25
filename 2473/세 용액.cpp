#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long LL;

vector<LL> liquid;

LL getSum(LL start, LL mid, LL end) {
	return liquid[start] + liquid[mid] + liquid[end];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	liquid.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> liquid[i];
	}

	sort(liquid.begin(), liquid.end());

	LL startLiquid, midLiquid, endLiquid;
	LL gap = LONG_LONG_MAX;
	for (int i = 0; i < n - 2; i++) {
		int start = i, mid = start + 1, end = n - 1;
		while (mid < end) {
			if (gap > abs(getSum(start, mid, end))) {
				startLiquid = liquid[start], midLiquid = liquid[mid], endLiquid = liquid[end];
				gap = abs(getSum(start, mid, end));
			}
			if (end < n - 1 && abs(getSum(start, mid, end + 1)) < abs(getSum(start, mid, end))) {
				end++;
				continue;
			}
			if (end > mid && abs(getSum(start, mid, end - 1)) < abs(getSum(start, mid, end))) {
				end--;
				continue;
			}
			mid++;
		}
	}

	cout << startLiquid << ' ' << midLiquid << ' ' << endLiquid;

	return 0;
}
