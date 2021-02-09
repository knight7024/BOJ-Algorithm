#include <iostream>
#include <stack>
#include <vector>
#define endl '\n'
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

	vector<char> answer;
	stack<int> simul;
	int idx = 0;
	for (int i = 1; i <= n; i++) {
		simul.push(i);
		answer.push_back('+');
		while (!simul.empty() && simul.top() >= arr[idx]) {
			while (!simul.empty() && simul.top() >= arr[idx]) {
				simul.pop();
				answer.push_back('-');
			}
			idx++;
		}
	}

	if (idx == n) {
		for (char c : answer) {
			cout << c << endl;
		}
	}
	else {
		cout << "NO";
	}

	return 0;
}
