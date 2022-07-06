#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    long n, m;
    cin >> n >> m;

    vector<pair<long, long>> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }

    int start = 0, end = 0;
    long sumFlavor = arr[0].first;
    priority_queue<pair<long, int>> pq; pq.emplace(arr[0].second, 0);
    long answer = LONG_MAX;
    while (start <= end and end < n) {
        if (sumFlavor >= m) {
            while (pq.top().second < start) pq.pop();
            answer = min(answer, pq.top().first);
        }
        if (sumFlavor <= m or start == end) {
            sumFlavor += arr[++end].first;
            pq.emplace(arr[end].second, end);
        }
        else if (sumFlavor > m or end >= n - 1) sumFlavor -= arr[start++].first;
    }

    cout << answer;
    
    return 0;
}
