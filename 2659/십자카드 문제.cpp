#include <iostream>

using namespace std;

int getMinClockwiseNum(int num) {
	int cwNum = num;
	int minCwNum = num;
	for (int i = 0; i < 3; i++) {
		cwNum = cwNum % 1000 * 10 + cwNum / 1000;
		minCwNum = min(minCwNum, cwNum);
	}
	return minCwNum;
}

int main() {
	int arr[4];
	cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];

	int result = getMinClockwiseNum(arr[0] * 1000 + arr[1] * 100 + arr[2] * 10 + arr[3]);
	int ans = 0;
	for (int i = 1111; i <= result; i++) {
		if (getMinClockwiseNum(i) == i) ans++;
	}
	cout << ans;
	return 0;
}
