#include <algorithm>
#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	
	int n;
	cin >> n;

	vector<int> v(n + 1);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	pair<int, int> mx[100001];
	pair<int, int> mn[100001];
	int answer = INF;
	int maxV = -1, minV = INF;
	int maxP = -1, minP = -1;
	for (int i = n - 1; i >= 0; i--) {
		if (maxV <= v[i]) {
			maxV = v[i];
			maxP = i;
		}
		if (minV >= v[i]) {
			minV = v[i];
			minP = i;
		}
		mx[i] = {maxV, maxP};
		mn[i] = {minV, minP};
	}

	int tmp = -1;
	for (int i = 0; i < n; i++) {
		if (mx[i].first - mn[i].first >= tmp) {
			tmp = mx[i].first - mn[i].first;
			answer = min(answer, abs(mx[i].second - mn[i].second));
		}
	}
	cout << answer + 1;
}
