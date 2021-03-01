#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX 2147483647
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	long count = 0;
	stack<pair<int, int>> cow;
	cow.emplace(MAX, n);
	for (int i = n - 1; i >= 0; i--) {
		while (cow.top().first < arr[i]) cow.pop();

		if (cow.top().first >= arr[i]) {
			count += cow.top().second - i - 1;
			cow.emplace(arr[i], i);
		}
	}

	cout << count;
	
	return 0;
}
