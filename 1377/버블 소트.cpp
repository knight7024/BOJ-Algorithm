#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;

	vector<pair<int, int>> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}

	sort(arr.begin(), arr.end());

	int answer = 0;
	for (int i = 0; i < n; i++) {
		answer = max(answer, arr[i].second - i);
	}

	cout << answer + 1;

	return 0;
}
