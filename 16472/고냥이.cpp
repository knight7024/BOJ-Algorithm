#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
	int n;
	cin >> n;

	string s;
	cin >> s;

	int answer = 0;
	int start = 1, end = 100000;
	while (start <= end) {
		int mid = (start + end) / 2;

		int minLen = s.size();
		int uniqAlphabet = 0;
		if (mid <= s.size()) {
			int check[26] {};
			// 슬라이딩 윈도우 기법을 이용하여 최적화
			for (int i = 0; i < mid; i++) {
				if (!check[s[i] - 'a']) uniqAlphabet++;
				check[s[i] - 'a']++;
			}
			minLen = min(minLen, uniqAlphabet);
			if (uniqAlphabet == n) answer = max(answer, mid);
			for (int i = mid; i < s.size(); i++) {
				if (check[s[i - mid] - 'a']) {
					check[s[i - mid] - 'a']--;
					if (!check[s[i - mid] - 'a']) uniqAlphabet--;
				}
				if (!check[s[i] - 'a']) uniqAlphabet++;
				check[s[i] - 'a']++;
				minLen = min(minLen, uniqAlphabet);
				if (uniqAlphabet == n) answer = max(answer, mid);
			}
		}

		if (minLen == s.size() || minLen > n) end = mid - 1;
		else start = mid + 1;
	}

	cout << (answer ? answer : s.size());

}
