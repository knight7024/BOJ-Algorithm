#include <iostream>
#include <vector>
#include <string>
using namespace std;

int minCount = 0x3f, maxCount;

int countOdds(string& s) {
	int count = 0;
	for (char c : s) count += (c - '0') % 2;
	return count;
}

void divide(string s, int count) {
	// 수가 한 자리이면 더 이상 아무것도 하지 못하고 종료한다.
	if (s.size() == 1) {
		maxCount = max(maxCount, count + countOdds(s));
		minCount = min(minCount, count + countOdds(s));
		return;
	}

	// 수가 두 자리이면 2개로 나눠서 합을 구하여 새로운 수로 생각한다.
	if (s.size() == 2) {
		divide(to_string((s[0] - '0') + (s[1] - '0')), count + countOdds(s));
		return;
	}

	// 수가 세 자리 이상이면,
	for (int i = 1; i < s.size() - 1; i++) {
		for (int j = i + 1; j < s.size(); j++) {
			// 임의의 위치에서 끊어서 3개의 수로 분할하고,
			string partial1 = s.substr(0, i), partial2 = s.substr(i, j - i), partial3 = s.substr(j);
			// 3개를 더한 값을 새로운 수로 생각한다.
			string newS = to_string(stoi(partial1) + stoi(partial2) + stoi(partial3));
			divide(newS, count + countOdds(s));
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	string s;
	cin >> s;

	divide(s, 0);

	cout << minCount << ' ' << maxCount;

	return 0;
}
