#include <bits/stdc++.h>
using namespace std;

long getCapacity(long mid, vector<long>& times) {
    long result = 0;
    for (long i : times) result += mid / i;
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    long n, m;
    cin >> n >> m;

    vector<long> times(n);
    long maxTime = 1;
    for (int i = 0; i < n; i++) {
        cin >> times[i];
        maxTime = max(maxTime, times[i]);
    }

    long start = 0, end = maxTime * m + 1;
    while (start + 1 < end) {
        long mid = end - (end - start) / 2;
        if (getCapacity(mid, times) < m) start = mid;
        else end = mid;
    }

    cout << end;

    return 0;
}
