#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<int> liquid(n);
	for (int i = 0; i < n; i++) {
		cin >> liquid[i];
	}

	sort(liquid.begin(), liquid.end());

	int start = 0, end = n - 1;
	int startLiquid = liquid[start], endLiquid = liquid[end];
	int gap = abs(endLiquid + startLiquid);
	while (start < end) {
		if (abs(liquid[end] + liquid[start]) < gap) {
			startLiquid = liquid[start];
			endLiquid = liquid[end];
			gap = abs(endLiquid + startLiquid);
		}
		if (end > mid && abs(liquid[end - 1] + liquid[start]) < abs(liquid[end] + liquid[start])) {
			end--;
			continue;
		}
		if (end < n - 1 && abs(liquid[end + 1] + liquid[start]) < abs(liquid[end] + liquid[start])) {
			++end;
			continue;
		}
		start++;
	}

	cout << startLiquid << ' ' << endLiquid;
	return 0;
}
