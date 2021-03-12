#include <iostream>
#include <algorithm>
#define MIN -1000
using namespace std;

int n;
int farm[303][303];
int prefixSumY[303][303];
int prefixSumX[303][303];

int search(int w) {
	int maxProfit = MIN;
	int fromY = 1, fromX = 1;
	int toY = fromY + w - 1, toX = fromX + w - 1;
	// init
	int profit = 0;
	for (int i = fromY; i <= toY; i++) {
		for (int j = fromX; j <= toX; j++) {
			profit += farm[i][j];
		}
	}
	maxProfit = max(maxProfit, profit);
	while (1) {
		int tempProfit = profit;
		// 오른쪽으로 이동
		while (toX < n) {
			fromX++; toX++;
			tempProfit -= prefixSumY[toY][fromX - 1] - prefixSumY[fromY - 1][fromX - 1];
			tempProfit += prefixSumY[toY][toX] - prefixSumY[fromY - 1][toX];
			maxProfit = max(maxProfit, tempProfit);
		}
		if (toY >= n) break;
		// 아래로 이동
		fromX = 1; toX = fromX + w - 1;
		fromY++; toY++;
		profit -= prefixSumX[fromY - 1][toX] - prefixSumX[fromY - 1][fromX - 1];
		profit += prefixSumX[toY][toX] - prefixSumX[toY][fromX - 1];
		maxProfit = max(maxProfit, profit);
	}

	return maxProfit;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> farm[i][j];
		}
	}

	// y축 누적합
	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= n; i++) {
			prefixSumY[i][j] = prefixSumY[i - 1][j] + farm[i][j];
		}
	}

	// x축 누적합
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			prefixSumX[i][j] = prefixSumX[i][j - 1] + farm[i][j];
		}
	}

	// Sliding Window
	int answer = MIN;
	for (int i = 1; i <= n; i++) {
		answer = max(answer, search(i));
	}

	cout << answer;

	return 0;
}
