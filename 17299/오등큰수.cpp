#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<int> arr(n);
	int check[1000001] {};
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		check[arr[i]]++;
	}

	vector<int> answer;
	stack<pair<int, int>> ngf;
	for (int i = n - 1; i >= 0; i--) {
		while (!ngf.empty() && ngf.top().second <= check[arr[i]]) ngf.pop();

		if (ngf.empty()) {
			answer.push_back(-1);
			ngf.emplace(arr[i], check[arr[i]]);
			continue;
		}

		answer.push_back(ngf.top().first);
		ngf.emplace(arr[i], check[arr[i]]);
	}

	for (int i = n - 1; i >= 0; i--) cout << answer[i] << ' ';

	return 0;
}
