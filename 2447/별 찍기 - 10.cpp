#include <iostream>
#define endl '\n'
using namespace std;

bool star[2200][2200];

// 분할정복
void star10(int y, int x, int n) {
	if (n == 1) {
		star[y][x] = true;
		return;
	}

	star10(y, x, n / 3);
	star10(y, x + n / 3, n / 3);
	star10(y, x + n / 3 * 2, n / 3);
	star10(y + n / 3, x, n / 3);
	star10(y + n / 3, x + n / 3 * 2, n / 3);
	star10(y + n / 3 * 2, x, n / 3);
	star10(y + n / 3 * 2, x + n / 3, n / 3);
	star10(y + n / 3 * 2, x + n / 3 * 2, n / 3);
}

int main() {
	cout.tie(0);

	int n;
	cin >> n;

	star10(0, 0, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << (star[i][j] ? '*' : ' ');
		}
		cout << endl;
	}

	return 0;
}
