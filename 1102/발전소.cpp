#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX 16
using namespace std;

const int INF = 0x3f3f3f3f;

int n, p;
int cost[MAX][MAX];
int dp[1 << MAX];

int recur(int state) {
	// p개 이상의 발전소가 고장나 있지 않다면 그대로 반환
	// 최소 비용을 구하는 것이기 때문에 최소의 발전소만 고쳐야 한다.
	if (__builtin_popcount(state) >= p) return 0;
	int& ret = dp[state];
	if (ret != INF) return ret;

	int result = INF;
	for (int i = 0; i < n; i++) {
		// 켜져있는 발전소에서
		if (!(state & (1 << i))) continue;
		for (int j = 0; j < n; j++) {
			// 꺼져있는 발전소를 고친다.
			if (state & (1 << j)) continue;
			result = min(result, recur(state | (1 << j)) + cost[i][j]);
		}
	}

	return ret = result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> cost[i][j];
		}
	}

	int state = 0;
	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		if (c == 'Y') state |= (1 << i);
	}

	cin >> p;

	memset(dp, INF, sizeof(dp));

	int answer = recur(state);
	cout << (answer == INF ? -1 : answer);

	return 0;
}
