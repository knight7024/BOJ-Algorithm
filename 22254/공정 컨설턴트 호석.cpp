#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
  
    int n, x;
    cin >> n >> x;

    vector<int> times(n);
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    int start = 0, end = n + 1;
    while (start + 1 < end) {
        int mid = (start + end) >> 1;

        pq = {};
        int result = 0;
        for (int i = 1; i <= mid; i++) {
            pq.emplace(times[i - 1], i);
            result = max(result, times[i - 1]);
        }

        for (int i = mid; i < n; i++) {
            auto top = pq.top();
            pq.pop();
            top.first += times[i];
            pq.emplace(top);
            result = max(result, top.first);
        }

        if (result > x) start = mid;
        else end = mid;
    }

    cout << end;
    
    return 0;
}
