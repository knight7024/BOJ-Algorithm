#include <iostream>
#include <vector>
#define ll unsigned long long

using namespace std;

// 제곱ㄴㄴ수가 되기 위한 조건
// 1. 소인수들이 소수여야 한다.
// 2. 소인수의 개수가 각각 1개여야 한다.
// 즉, 소수의 제곱으로 나누어 떨어진다면 제곱ㄴㄴ수가 될 수 없다.

// false여야 소수
bool eratos[1000001];
// false여야 제곱ㄴㄴ수
bool result[1000001];
vector<int> prime;

void init(ll max) {
	// 에라토스테네스의 체로 소수들을 모두 구한다.
	for (ll i = 2; i * i <= max; i++) {
		if (eratos[i]) continue;
		// 단, 제곱근 범위까지의 소수들만 구한다.
		// ex) 36이면 6까지만인 2 3 5
		for (ll j = i * i; j * j <= max; j += i) {
			eratos[j] = true;
		}
		prime.push_back(i);
	}
}

int main() {
	ll min, max;
	cin >> min >> max;

	init(max);

	for (int i = 0; i < prime.size(); i++) {
		// 소수의 제곱
		ll d = (ll)prime[i] * prime[i];

		// min 이상의 수 중에서 소수로 나누어 떨어지는 수의 몫
		ll minQ = min % d ? min / d + 1 : min / d;
		// max 이하의 수 중에서 소수로 나누어 떨어지는 수의 몫
		ll maxQ = max / d;
		// 그 사이의 범위에서 에라토스테네스의 체를 수행한다.
		for (ll j = minQ; j <= maxQ; j++) {
			result[d * j - min] = true;
		}
	}

	int answer = 0;
	for (int i = 0; i <= max - min; i++) answer += !result[i];

	cout << answer;
	return 0;
}
