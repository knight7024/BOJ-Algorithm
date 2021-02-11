#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int k, n;
	cin >> k >> n;

	vector<int> wlan(k);
	for (int i = 0; i < k; i++) {
		cin >> wlan[i];
	}

	long answer = 0;
	long start = 1, end = (1 << 31) - 1;
	while (start <= end) {
		long mid = (start + end) / 2;
		
		long count = 0;
		for (int i : wlan) count += i / mid;

		if (count >= n) {
			answer = max(answer, mid);
			start = mid + 1;
		}
		else end = mid - 1;
	}

	cout << answer;

	return 0;
}
