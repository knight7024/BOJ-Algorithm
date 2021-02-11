#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1'000'000'000
using namespace std;

int main() {
	int n, c;
	cin >> n >> c;

	vector<long> house(n);
	for (int i = 0; i < n; i++) {
		cin >> house[i];
	}

	sort(house.begin(), house.end());

	long answer = 0;
	long start = 0, end = MAX;
	while (start < end) {
		long mid = (start + end) / 2;

		int installed = 0;
		int x = 0;
		while (x < n) {
			installed++;
			x = distance(house.begin(), lower_bound(house.begin(), house.end(), house[x] + mid));
		}

		if (installed >= c) {
			answer = max(answer, mid);
			start = mid + 1;
		}
		else end = mid;
	}

	cout << answer;

	return 0;
}
