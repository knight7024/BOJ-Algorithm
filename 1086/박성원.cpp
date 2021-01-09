#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

struct NumInfo {
	int mod;
	int expandDigit;
};

int n, k;
vector<NumInfo> arr;
// [A][B]: A를 사용한 상태인데 나머지가 B인 경우
LL dp[1 << 15][100];

// 분할정복 거듭제곱
int pow(int a, int b) {
    if (!b) return 1;
    int n = pow(a, b / 2) % k;
	return b % 2 ? (a * (n % k) * (n % k)) % k : (n % k) * (n % k);
}

LL dfs(int state, int mod) {
	// 더 이상 합칠 정수가 없다면
	if (state == (1 << n) - 1) return mod == 0;
	LL& ret = dp[state][mod];
	if (ret != -1) return ret;

	LL result = 0;
	for (int i = 0; i < n; i++) {
		if (state & (1 << i)) continue;
		LL mult = (mod * arr[i].expandDigit + arr[i].mod) % k;
		result += dfs(state | (1 << i), mult);
	}

	return ret = result;
}

LL gcd(LL a, LL b) {
	return !b ? a : gcd(b, a % b);
}

LL getFactorial(int n) {
	LL result = 1;
	for (int i = 2; i <= n; i++) result *= i;
	return result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	string num[16];
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}

	cin >> k;

	for (int i = 0; i < n; i++) {
		// 큰 수를 k로 나눈 나머지 구하기
		int prev = 0;
		for (char c : num[i]) {
			prev *= 10;
			prev = (prev % k + (c - '0')) % k;
		}
		arr.push_back({prev, pow(10, (int) num[i].size())});
	}

	memset(dp, -1, sizeof(dp));

	LL p = 0;
	for (int i = 0; i < n; i++) {
		p += dfs(1 << i, arr[i].mod);
	}

	LL q = getFactorial(n);
	LL g = gcd(p, q);

	if (!p) cout << "0/1";
	else cout << p / g << '/' << q / g;
	
	return 0;
}
