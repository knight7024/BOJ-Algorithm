#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    auto sixthNum = [&](int n) -> int {
        return (2 * n - 1) * n;
    };

    int n;
    cin >> n;

    vector<int> arr;
    int dp[1000001]; fill(&dp[0], &dp[n + 1], 6);
    for (int i = 1; i <= n; i++) {
        int t = sixthNum(i);
        if (t > n) break;
        arr.push_back(t);
        dp[t] = 1;
    }

    for (int j = 2; j <= n; j++) {
        for (int i : arr) {
            if (j < i) break;
            dp[j] = min(dp[j], dp[j - i] + 1);
        }
    }

    cout << dp[n];
    
    return 0;
}
