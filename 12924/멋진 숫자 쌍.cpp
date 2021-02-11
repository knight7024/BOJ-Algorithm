#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int a, b;

long rotate(int n) {
	int tempN = n;
	string num;
	while (n) {
		num.push_back((n % 10) + '0');
		n /= 10;
	}
	reverse(num.begin(), num.end());

	long result = 0;
	while (1) {
		// 회전
		for (int i = 0; i < num.size() - 1; i++) {
			swap(num[i], num[i + 1]);
		}

		if (num[0] != '0') {
			// 문자를 숫자로
			int realNum = stoi(num);
			if (realNum == tempN) break;
			if (realNum >= a && realNum <= b) {
				result++;
			}
		}
	}

	return result;
}

int main() {
	cin >> a >> b;

	long answer = 0;
	for (int i = a; i <= b; i++) {
		answer += rotate(i);
	}

	cout << answer / 2;

	return 0;
}
