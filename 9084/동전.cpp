#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int n;
vector<int> coins;
int dp[20][100001];

int dfs(int idx, int target) {
    if (idx >= n) return target == 0;

    int& ret = dp[idx][target];
    if (ret != -1) return ret;

    ret = 0;
    for (int j = 0; j <= target / coins[idx]; j++) {
        ret += dfs(idx + 1, target - j * coins[idx]);
    }

    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        cin >> n;
        coins.resize(n);

        for (int i = 0; i < n; i++) {
            cin >> coins[i];
        }

        int m;
        cin >> m;

        memset(dp, -1, sizeof(dp));
        cout << dfs(0, m) << endl;
    }

    return 0;
}
