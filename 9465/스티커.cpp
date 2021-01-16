#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int sticker[2][100001];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                cin >> sticker[i][j];
            }
        }

        //0: 안 뗌, 1: 위 뗌, 2: 아래 뗌
        int dp[100001][3];
        dp[0][0] = 0;
        dp[0][1] = sticker[0][0];
        dp[0][2] = sticker[1][0];
        for (int j = 1; j < n; j++) {
            dp[j][0] = max(dp[j - 1][0], max(dp[j - 1][1], dp[j - 1][2]));
            dp[j][1] = sticker[0][j] + max(dp[j - 1][0], dp[j - 1][2]);
            dp[j][2] = sticker[1][j] + max(dp[j - 1][0], dp[j - 1][1]);
        }

        cout << max(dp[n - 1][0], max(dp[n - 1][1], dp[n - 1][2])) << endl;
    }

    return 0;
}
