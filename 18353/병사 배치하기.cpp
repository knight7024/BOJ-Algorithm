#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int result = 0;
	int dp[2001] {};
	for (int i = n - 1; i >= 0; i--) {
		if (!dp[i]) dp[i] = 1;
		for (int j = i + 1; j < n; j++) {
			if (arr[i] > arr[j]) dp[i] = max(dp[i], dp[j] + 1);
		}
		result = max(result, dp[i]);
	}

	cout << n - result;

    return 0;
}
