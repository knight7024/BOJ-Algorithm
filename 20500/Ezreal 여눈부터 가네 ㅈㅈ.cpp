#include <bits/stdc++.h>
using namespace std;

const int MOD = 1'000'000'007;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;

    long dp[1516][15] {};
    dp[1][1] = dp[1][5] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 15; j++) {
            dp[i + 1][(j * 10 + 1) % 15] += dp[i][j];
            dp[i + 1][(j * 10 + 1) % 15] %= MOD;
            
            dp[i + 1][(j * 10 + 5) % 15] += dp[i][j];
            dp[i + 1][(j * 10 + 5) % 15] %= MOD;
        }
    }

    cout << dp[n][0];
    
    return 0;
}
