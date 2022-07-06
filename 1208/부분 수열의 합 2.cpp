#include <bits/stdc++.h>
using namespace std;

void recur(int pos, long sum, vector<int>& from, vector<long>& to) {
    if (pos >= from.size()) return;
    recur(pos + 1, sum, from, to);
    to.push_back(sum + from[pos]);
    recur(pos + 1, sum + from[pos], from, to);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; long s;
    cin >> n >> s;

    vector<int> divArr1, divArr2;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        (i < n / 2 ? divArr1 : divArr2).push_back(x);
    }

    vector<long> arr1, arr2;
    recur(0, 0, divArr1, arr1);
    recur(0, 0, divArr2, arr2);

    sort(arr2.begin(), arr2.end());

    long answer = 0;
    for (long& a : arr1) {
        answer += a == s;
        answer += upper_bound(arr2.begin(), arr2.end(), s - a) - 
            lower_bound(arr2.begin(), arr2.end(), s - a);
    }
    for (long& b : arr2) answer += b == s;

    cout << answer;
    
    return 0;
}
