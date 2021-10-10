#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int INF = 0x3f3f3f3f;
int dp[5001];

int dfs(int n) {
    if (n < 3) return INF;
    if (n == 3 || n == 5) return 1;
    
    int& ret = dp[n];
    if (ret != INF) return ret;

    int result = min(dfs(n - 3), dfs(n - 5));
    return result == INF ? INF : ret = result + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    memset(dp, INF, sizeof(dp));

    int ans = dfs(n);
    cout << (ans == INF ? -1 : ans);
	return 0;
}
