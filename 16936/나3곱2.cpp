#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<long> arr;

bool dfs(int idx, int depth, vector<long>& route) {
	route.push_back(arr[idx]);

	if (depth == n) {
		for (long i : route) cout << i << ' ';
		return true;
	}

	bool result = false;
	// 나3
	if (arr[idx] % 3 == 0) {
		auto nextIt = lower_bound(arr.begin(), arr.end(), arr[idx] / 3);
		if (nextIt != arr.end() && *nextIt == arr[idx] / 3) {
			result |= dfs(distance(arr.begin(), nextIt), depth + 1, route);
		}
	}

	// 곱2
	auto nextIt = lower_bound(arr.begin(), arr.end(), arr[idx] * 2);
	if (nextIt != arr.end() && *nextIt == arr[idx] * 2) {
		result |= dfs(distance(arr.begin(), nextIt), depth + 1, route);
	}

	route.pop_back();
	
	return result;
}

int main() {
	cin >> n;

	arr.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	sort(arr.begin(), arr.end());

	vector<long> route;
	for (int i = 0; i < n; i++) {
		if (dfs(i, 1, route)) break;
	}

	return 0;
}
