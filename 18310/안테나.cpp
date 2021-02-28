#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 2147483647
using namespace std;

const int dy[] = {0, 0, -1, 1};
const int dx[] = {-1, 1, 0, 0};


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<long> house(n);
	for (int i = 0; i < n; i++) {
		cin >> house[i];
	}

	sort(house.begin(), house.end());

	vector<long> prefixSum(1, house[0]);
	for (int i = 1; i < n; i++) {
		prefixSum.push_back(prefixSum.back() + house[i]);
	}

	long minDist = MAX;
	long answer = 0;
	for (int i = 0; i < n; i++) {
		long dist = (house[i] * (i + 1) - prefixSum[i]) + ((prefixSum.back() - prefixSum[i]) - house[i] * (n - i - 1));
		if (minDist > dist) {
			minDist = dist;
			answer = house[i];
		}
	}

	cout << answer;

    return 0;
}
