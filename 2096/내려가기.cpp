#include <iostream>
#include <cstring>
#include <algorithm>
#define INF 987654321
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	int game[100001][3];
	for (int i = 0; i < n; i++) {
		cin >> game[i][0] >> game[i][1] >> game[i][2];
	}

	int dpMin[2][3], dpMax[2][3];
  
	// 미리 값 초기화
	for (int j = 0; j < 3; j++) {
		dpMin[(n - 1) % 2][j] = dpMax[(n - 1) % 2][j] = game[n - 1][j];
	}

	for (int i = n - 1; i >= 1; i--) {
		int nowIdx = i % 2;
		int nextIdx = i % 2 ? 0 : 1;

		// 다음 값의 대소를 비교하기 위해 매 번 초기화 해준다.
		dpMin[nextIdx][0] = dpMin[nextIdx][1] = dpMin[nextIdx][2] = INF;
		dpMax[nextIdx][0] = dpMax[nextIdx][1] = dpMax[nextIdx][2] = -1;

		for (int j = 0; j < 3; j++) {
			// ↖
			if (j - 1 >= 0) {
				dpMin[nextIdx][j - 1] = min(dpMin[nextIdx][j - 1], game[i - 1][j - 1] + dpMin[nowIdx][j]);
				dpMax[nextIdx][j - 1] = max(dpMax[nextIdx][j - 1], game[i - 1][j - 1] + dpMax[nowIdx][j]);
			}
			// ↑
			dpMin[nextIdx][j] = min(dpMin[nextIdx][j], game[i - 1][j] + dpMin[nowIdx][j]);
			dpMax[nextIdx][j] = max(dpMax[nextIdx][j], game[i - 1][j] + dpMax[nowIdx][j]);
			// ↗
			if (j + 1 < 3) {
				dpMin[nextIdx][j + 1] = min(dpMin[nextIdx][j + 1], game[i - 1][j + 1] + dpMin[nowIdx][j]);
				dpMax[nextIdx][j + 1] = max(dpMax[nextIdx][j + 1], game[i - 1][j + 1] + dpMax[nowIdx][j]);
			}
		}
	}

	cout << max(dpMax[0][0], max(dpMax[0][1], dpMax[0][2])) << ' ' << min(dpMin[0][0], min(dpMin[0][1], dpMin[0][2]));
	return 0;
}
