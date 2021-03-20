#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n, k, b;
	cin >> n >> k >> b;

	vector<int> traffic(b);
	for (int i = 0; i < b; i++) {
		cin >> traffic[i];
	}

	sort(traffic.begin(), traffic.end());

	int answer = b;
	for (int i = 1; i <= n - k + 1; i++) {
		auto from = lower_bound(traffic.begin(), traffic.end(), i);
		auto to = upper_bound(traffic.begin(), traffic.end(), i + k - 1);
		answer = min(answer, (int) (to - from));
	}

	cout << answer;

	return 0;
}
