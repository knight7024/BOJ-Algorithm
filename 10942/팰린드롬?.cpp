#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

vector<int> arr;
int dp[2000][2000];

int dfs(int s, int e) {
    if (s == e) return 1;
    else if (e - s == 1) return arr[s] == arr[e];
    int& ret = dp[s][e];
    if (ret != -1) return ret;

    return ret = dfs(s + 1, e - 1) & (arr[s] == arr[e]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int m;
    cin >> m;

    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < m; i++) {
        int s, e;
        cin >> s >> e;
        cout << dfs(s - 1, e - 1) << endl;
    }
    
    return 0;
}
