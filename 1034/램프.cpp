#include <iostream>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	bool lamp[50][50];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			lamp[i][j] = c == '1';
		}
	}

	int k;
	cin >> k;

	int answer = 0;
	for (int i = 0; i < n; i++) {
		int offCount = 0;
		for (int j = 0; j < m; j++) offCount += !lamp[i][j];
		
		// 꺼진 램프의 개수와 k가 같이 홀수거나 짝수인 경우 찾고
		// 해당 행을 모두 켰을 때 같이 켜지는 행 찾기
		int sameCount = 0;
		if (offCount <= k && (k - offCount) % 2 == 0) {
			for (int ii = 0; ii < n; ii++) {
				bool isSame = true;
				for (int j = 0; j < m; j++) {
					if (lamp[i][j] != lamp[ii][j]) {
						isSame = false;
						break;
					}
				}
				sameCount += isSame;
			}
		}
		answer = max(answer, sameCount);
	}

	cout << answer;

	return 0;
}
