#include <iostream>
#include <string>
#define endl '\n'
using namespace std;

string s;

void backtracking(int size, int idx, string& partialS) {
	if (!size) {
		cout << partialS << endl;
		return;
	}

	char minChar = 'Z' + 1;
	int minIdx = -1;
	for (int i = idx; s.size() - i >= size; i++) {
		if (minChar > s[i]) {
			minChar = s[i];
			minIdx = i;
		}
	}

	partialS.push_back(minChar);
	backtracking(size - 1, minIdx + 1, partialS);
	partialS.pop_back();
}

int main() {
	cin >> s;

	string partialS = "";
	for (int i = 1; i <= s.size(); i++) {
		backtracking(i, 0, partialS);
	}

	return 0;
}
