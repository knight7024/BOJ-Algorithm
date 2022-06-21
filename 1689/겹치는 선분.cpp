#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }

    sort(arr.begin(), arr.end());

    int answer = 0;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < n; i++) {
        while (!pq.empty() and pq.top() <= arr[i].first) pq.pop();
        pq.push(arr[i].second);
        answer = max(answer, (int) pq.size());
    }

    cout << answer;
    
    return 0;
}
