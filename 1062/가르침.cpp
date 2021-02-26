#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> study;
bool check[26] {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
vector<char> spelling;
int answer;

void checkString() {
	int result = 0;
	for (string& s : study) {
		bool flag = true;
		for (int i = 4; i < s.size() - 4; i++) {
			if (check[s[i] - 'a']) continue;
			flag = false;
			break;
		}
		result += flag;
	}
	answer = max(answer, result);
}

void combination(int r, int idx) {
	if (!r) {
		checkString();
		return;
	}

	for (int i = idx; i < spelling.size(); i++) {
		check[spelling[i] - 'a'] = true;
		combination(r - 1, i + 1);
		check[spelling[i] - 'a'] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	study.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> study[i];
	}

	// antatica로 배울 수 있는 단어는 5개이므로
	if (k < 5) {
		cout << 0;
		exit(0);
	}

	for (string& s : study) {
		for (int i = 4; i < s.size() - 4; i++) {
			if (check[s[i] - 'a']) continue;
			spelling.push_back(s[i]);
		}
	}

	sort(spelling.begin(), spelling.end());

	spelling.erase(unique(spelling.begin(), spelling.end()), spelling.end());

	// 다 배울 수 있는 경우
	if (spelling.size() <= k - 5) {
		cout << n;
		exit(0);
	}

	combination(k - 5, 0);

	cout << answer;

	return 0;
}
