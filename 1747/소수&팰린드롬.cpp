#include <iostream>
#define MAX 1003001
using namespace std;

// false가 소수
bool erath[MAX];

bool isPalindrome(int n) {
	int tempN = n;
	int newN = 0;
	while (tempN) {
		newN = newN * 10 + tempN % 10;
		tempN /= 10;
	}

	return newN == n;
}

int getPrimeAndPal(int n) {
	int maxN = 1;
	for (long i = 2; i <= MAX; i++) {
		if (erath[i]) continue;
		for (long j = i * i; j <= MAX; j += i) {
			erath[j] = true;
		}
		if (maxN < i) {
			if (isPalindrome(i)) maxN = i;
			if (maxN >= n) break;
		}
	}

	return maxN;
}

int main() {
	int n;
	cin >> n;

	// 아래 소스로 소수이면서 팰린드롬인 수 중 가장 작은 수가 1003001임을 구한 후
	// cout << getPrimeAndPal(1000000000);

	cout << getPrimeAndPal(n);

	return 0;
}
