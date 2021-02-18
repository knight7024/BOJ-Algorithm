#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define MIN -1000
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;

	vector<long> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	long answer = LONG_MIN;
	long dp[100001][2] {{MIN, MIN}};
	for (int i = 1; i <= n; i++) {
		dp[i][0] = max(dp[i - 1][0] + arr[i - 1], arr[i - 1]);
		dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + arr[i - 1]);
		answer = max(max(answer, dp[i][0]), dp[i][1]);
	}

	cout << answer;

	return 0;
}
