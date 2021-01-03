#include <iostream>
#include <algorithm>
#define MOD 1000000
using namespace std;

typedef long long ll;

ll arr[101][101];

// 조합론
ll combination(int n, int r) {
	for (int i = 0; i <= n; i++){
		for (int j = 0; j <= r; j++){
			if(i == j || !j) arr[i][j] = 1;
			else arr[i][j] = arr[i - 1][j - 1] % MOD + arr[i - 1][j] % MOD;
		}
	}

	return arr[n][r] % MOD;
}

int main() {
	int n;
	cin >> n;

	ll dp[101] {0, 2, 2, 4};

	// 숫자가 i개 있을 때 i가 p 위치에 존재할 때 나머지가 존재할 가능성
	// 조합론 + DP 
	for (int i = 4; i <= n; i++) {
		ll result = 0;
		// 첫 번째 위치에 있을 때
		result += (dp[i - 1] / 2);
		// 두 번째 위치에 있을 때부터 절반 위치까지 (대칭을 이루기 때문)
		for (int p = 2; p <= i / 2; p++) {
			result += combination(i - 1, p - 1) * (dp[p - 1] / 2) * (dp[i - p] / 2);
		}
		// 대칭을 이루므로 2배해준다.
		result *= 2;
		// 홀수일 경우에는 중간값이 생기므로 따로 더해준다.
		if (i % 2) result += combination(i - 1, i / 2) * (dp[i / 2] / 2) * (dp[i - (i / 2 + 1)] / 2);
		dp[i] = result % MOD;
	}
	
	cout << (n == 1 ? 1 : dp[n]);
    return 0;
}
