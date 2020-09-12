#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#define APPLE 0
#define BANANA 1

using namespace std;

struct Info {
	char type;
	int num;
};

Info map[1502][1502];
// 사과면 0, 바나나면 1
int prefixMap[2][1502][1502];
// [A][B]: (A, B)칸까지 불도저가 밀었을 때 사과와 바나나의 최대 합
int dp[1502][1502];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int r, c;
	cin >> r >> c;

	string tree;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> tree;
			map[i][j].type = tree[0];
			map[i][j].num = stoi(tree.substr(1));

			// 사과 누적합 ↓
			prefixMap[map[i][j].type != 'B'][i][j] += prefixMap[map[i][j].type != 'B'][i - 1][j];
			// 바나나 누적합 ↓
			prefixMap[map[i][j].type == 'B'][i][j] += map[i][j].num + prefixMap[map[i][j].type == 'B'][i - 1][j];
		}
	}
	
	// 첫 번째 칸은 미리 저장해둔다.
	dp[1][1] = prefixMap[APPLE][r][1] - prefixMap[APPLE][0][1] - (map[1][1].type == 'A' ? map[1][1].num : 0);
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (j == 1 && i == 1) continue;

			// 누적합 배열을 이용하여 사과나무와 바나나나무 개수 세어준다.
			int b = prefixMap[BANANA][i - 1][j];
			int a = prefixMap[APPLE][r][j] - prefixMap[APPLE][i][j];
			int sum = a + b;

			int maxSum = -1;
			// ↖에서 왔을 때,
			if (i > 1 && j > 1) maxSum = max(maxSum, dp[i - 1][j - 1] + sum);
			// ←에서 왔을 때,
			if (j > 1) maxSum = max(maxSum, dp[i][j - 1] + sum);
			// ↑에서 왔을 때,
			// 아래로 불도저가 내려오면 사과나무의 개수만 줄어들기 때문에 빼준다.
			if (i > 1) maxSum = max(maxSum, dp[i - 1][j] - (map[i][j].type == 'A' ? map[i][j].num : 0));
			dp[i][j] = maxSum;
		}
	}

	cout << dp[r][c];
	return 0;
}
