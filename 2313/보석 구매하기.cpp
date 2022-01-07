#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> value(n, -1e7);
    vector<pair<int, int>> range(n);
    for (int t = 0; t < n; t++) {
        int l;
        cin >> l;

        vector<int> jewel(l);
        for (int i = 0; i < l; i++) {
            cin >> jewel[i];
        }

        int s = 0, e = 0;
        int sum = jewel[0];
        while (s < l) {
            if (value[t] < sum) {
                value[t] = sum;
                range[t] = {s, e};
            }
            else if (value[t] == sum && e - s < range[t].second - range[t].first) range[t] = {s, e};

            if (sum <= 0) {
                s = e = e + 1;
                if (s < l) sum = jewel[s];
                continue;
            }

            if (e + 1 < l) sum += jewel[++e];
            else break;
        }
    }

    long answer = 0;
    for (int i : value) answer += i;

    cout << answer << endl;
    
    for (auto& p : range) cout << p.first + 1 << ' ' << p.second + 1 << endl;

    return 0;
}
