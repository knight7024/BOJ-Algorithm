#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
	string s;
	cin >> s;

	stack<char> compress;
	stack<pair<int, int>> prev;
	int bracket = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') bracket++;
		else if (s[i] == ')') {
			int qLen = 0;
			while (!prev.empty() && prev.top().second == bracket) {
				qLen += prev.top().first;
				prev.pop();
			}
			bracket--;
			while (!compress.empty() && compress.top() != '(') {
				qLen++;
				compress.pop();
			}
			// ( pop
			compress.pop();
			int k = compress.top() - '0';
			prev.emplace(qLen * k, bracket);
			// K pop
			compress.pop();
			continue;
		}
		compress.push(s[i]);
	}

	int answer = 0;
	while (!prev.empty()) {
		answer += prev.top().first;
		prev.pop();
	}

	cout << answer + compress.size();

	return 0;
}
