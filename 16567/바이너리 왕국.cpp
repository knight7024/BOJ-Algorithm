#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n + 2);
    int count = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (arr[i] and !arr[i - 1]) count++;
    }

    for (int i = 0; i < m; i++) {
        int q;
        cin >> q;
        if (!q) {
            cout << count << ' ';
            continue;
        }
        int p;
        cin >> p;
        if (arr[p]) continue;
        arr[p] = 1;
        if (!arr[p - 1] and !arr[p + 1]) count++;
        else if (arr[p + 1] and arr[p - 1]) count--;
    }
    
    return 0;
}
