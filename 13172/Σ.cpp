#include <bits/stdc++.h>
using namespace std;

const long MOD = 1'000'000'007;

long pow(long base, long exp) {
    if (!exp) return 1;
    long half = pow(base, exp / 2) % MOD;
    return (((half * half) % MOD) * (exp & 1 ? base : 1)) % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m;
    cin >> m;

    long answer = 0;
    while (m--) {
        long n, s;
        cin >> n >> s;
        answer = (answer + (s * pow(n, (long) MOD - 2)) % MOD) % MOD;
    }

    cout << answer;

    return 0;
}
