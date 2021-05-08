#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#define endl '\n'
using namespace std;

int n;
string s;
int bracketCheck[201];
int bracketId;
bool comb[11];
set<string> answer;

int recur(int idx) {
	for (int i = idx; i < n; i++) {
		if (s[i] == '(') {
			int depth = ++bracketId;
			bracketCheck[i] = depth;
			bracketCheck[i = recur(i + 1)] = depth;
		}
		else if (s[i] == ')') return i;
	}

	return -1;
}

void backtracking(int id) {
	if (id > bracketId) {
		string result;
		for (int i = 0; i < n; i++) {
			if (bracketCheck[i] && !comb[bracketCheck[i]]) continue;
			result += s[i];
		}
		answer.insert(result);
		return;
	}

	comb[id] = true;
	backtracking(id + 1);
	comb[id] = false;
	backtracking(id + 1);
}

int main() {
	cin >> s;
	n = s.size();

	recur(0);
	backtracking(1);

	for (auto it = next(answer.cbegin(), 1); it != answer.cend(); it++) cout << *it << endl;

	return 0;
}
