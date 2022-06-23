#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    int answer = INT_MAX;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                int pos = lower_bound(arr.begin(), arr.end(), arr[i] + arr[j] - arr[k]) - arr.begin();
                for (int x = pos - 3; x <= pos + 3; x++) {
                    if (x < 0 or x >= n or x == i or x == j or x == k) continue;
                    answer = min(answer, abs(arr[i] + arr[j] - arr[k] - arr[x]));
                }
            }
        }
    }

    cout << answer;
    
    return 0;
}
