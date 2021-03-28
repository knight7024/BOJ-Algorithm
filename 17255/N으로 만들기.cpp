#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

string n;
unordered_set<string> hashset;

void dfs(string num, int from, int to) {
	string split = num.substr(num.size() - to + from - 1);
	int numSize = n.size() * (n.size() + 1) / 2;
	if (num.size() >= numSize) {
		if (split == n) hashset.insert(num);
		return;
	}

	// 뒤에다 숫자 붙임
	string backNumber = split;
	if (to + 1 < n.size()) backNumber += n[to + 1];
	// 앞에다 숫자 붙임
	string frontNumber = split;
	if (from - 1 >= 0) frontNumber = n[from - 1] + frontNumber;

	if (backNumber != split) dfs(num + backNumber, from, to + 1);
	if (frontNumber != split) dfs(num + frontNumber, from - 1, to);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin >> n;

	for (int i = 0; i < n.size(); i++) {
		string split = n.substr(i, 1);
		dfs(split, i, i);
	}

	cout << hashset.size();

	return 0;
}
