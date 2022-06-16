#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> prefixSum(1);
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        prefixSum.push_back(prefixSum.back() + s);
    }

    vector<int> rocks(k);
    for (int i = 0; i < k; i++) {
        cin >> rocks[i];
    }
    rocks.push_back(n + 1);

    vector<pair<int, int>> result;
    for (int i = 1; i <= k; i++) {
        int diff = prefixSum[rocks[i] - 1] - prefixSum[rocks[i - 1] - 1];
        result.emplace_back(diff, rocks[i - 1]);
    }

    sort(result.begin(), result.end(), [](pair<int, int>& a, pair<int, int>& b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first > b.first;
    });

    vector<int> answer;
    for (int i = 0; m; i++, m--) {
        answer.push_back(result[i].second);
    }

    sort(answer.begin(), answer.end());

    for (int i : answer) cout << i << endl;

    return 0;
}
