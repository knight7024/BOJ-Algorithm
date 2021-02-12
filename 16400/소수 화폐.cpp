#include <iostream>
#include <vector>
#include <algorithm>
#define MOD 123'456'789
using namespace std;

int main() {
    int n;
    cin >> n;

    // 소수 구하기
    vector <int> prime;
    bool sieve[40001] {};
    for (int i = 2; i <= n; i++) {
        if (!sieve[i]) prime.push_back(i);
        for (int j = i * i; j <= n; j += i) {
            sieve[j] = true;
        }
    }

    // 지불 방법의 수 구하기
    int dp[40001] {1, };
    for (int i: prime) {
        for (int j = 0; j <= n; j++) {
            if (i > j) continue;
            dp[j] = (dp[j] + dp[j - i] % MOD) % MOD;
        }
    }

    cout << dp[n];

    return 0;
}
