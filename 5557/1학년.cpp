#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

int n, m;
vector<int> nums;
int target;
long dp[101][2001];

long dfs(int idx, int sum) {
	if (sum < 0 || sum > 20) return 0;
	if (idx >= n - 1) return sum == target;
	long& ret = dp[idx][sum];
	if (ret) return ret;

	ret += dfs(idx + 1, sum + nums[idx]);
	ret += dfs(idx + 1, sum - nums[idx]);

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	nums.resize(n - 1);
	for (int i = 0; i < n - 1; i++) {
		cin >> nums[i];
	}

	cin >> target;
	
	cout << dfs(1, nums[0]);

	
	return 0;
}
