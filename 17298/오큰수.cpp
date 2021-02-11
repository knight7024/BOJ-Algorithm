#include <iostream>
#include <vector>
#include <stack>
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

	stack<int> nge;
	vector<int> answer;
	for (int i = n - 1; i >= 0; i--) {
		// 스택의 최상단에 있는 수가 현재 수보다 작으면
		// 더이상 필요없는 수이다.
		// 다음 오큰수는 현재 수가 될테니까
		while (!nge.empty() && nge.top() <= arr[i]) {
			nge.pop();
		}

		// 스택이 비었다면 오큰수는 -1이다.
		if (nge.empty()) {
			nge.push(arr[i]);
			answer.push_back(-1);
			continue;
		}

		answer.push_back(nge.top());
		nge.push(arr[i]);
	}

	for (auto it = answer.rbegin(); it != answer.rend(); it++) {
		cout << *it << ' ';
	}

	return 0;
}
