#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	long g;
	cin >> g;

	bool flag = true;
	for (long i = 1; i < g; i++) {
		long target = i * i + g;
		long start = i, end = 1e5;
		while (start <= end) {
			long mid = (start + end) / 2;
			if (mid * mid == target) {
				cout << mid << endl;
				flag = false;
				break;
			}
			else if (mid * mid > target) end = mid - 1;
			else start = mid + 1;
		}
	}

	if (flag) cout << -1;

	return 0;
}
