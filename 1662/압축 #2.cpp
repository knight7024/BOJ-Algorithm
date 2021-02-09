#include <iostream>
#include <string>
using namespace std;

string s;

pair<int, int> recur(int idx, bool isBracket) {
	int result = 0;

	int i = idx;
	for (; i < s.size(); i++) {
		if (isBracket && s[i] == ')') break;
		if (s[i + 1] == '(') {
			auto p = recur(i + 2, true);
			result += (s[i] - '0') * p.first;
			i = p.second;
			continue;
		}
		if (isdigit(s[i])) result++;
	}

	return {result, i};
}

int main() {
	cin >> s;

	cout << recur(0, false).first;

	return 0;
}
