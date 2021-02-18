#include <iostream>
#include <vector>
#include <algorithm>
#define MIN -987654321
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

	int answer = MIN;
	vector<int> dp(n + 1);
	for (int i = 1; i <= n; i++) {
		dp[i] = max(dp[i - 1] + arr[i - 1], arr[i - 1]);
		answer = max(answer, dp[i]);
	}

	cout << answer;

	return 0;
}
