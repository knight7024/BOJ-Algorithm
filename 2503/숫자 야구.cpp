#include <iostream>
#include <string>
#include <list>
using namespace std;

int ballCount(int a, int b) {
	string sa = to_string(a);
	string sb = to_string(b);
	int count = 0;
	// 숫자가 다른 위치에 있는 경우만 센다.
	for (int i = 0; i < sa.size(); i++) {
		char c = sa[i];
		count += (sb.find(c) != string::npos) && (sb.find(c) != i);
	}
	return count;
}

int strikeCount(int a, int b) {
	int count = 0;
	// 100의 자리수가 같은가?
	count += (a / 100) == (b / 100);
	a %= 100; b %= 100;
	// 10의 자리수가 같은가?
	count += (a / 10) == (b / 10);
	a %= 10; b %= 10;
	// 1의 자리수가 같은가?
	count += a == b;
	return count;
}

bool isUnique(int a) {
	string sa = to_string(a);
	return sa[0] != sa[1] && sa[0] != sa[2] && sa[1] != sa[2];
}

int main() {
	int n;
	cin >> n;
	
	list<int> myList;
	for (int i = 0; i < n; i++) {
		int q, s, b;
		cin >> q >> s >> b;

		// 처음이라면
		if (!i) {
			for (int num = 111; num <= 999; num++) {
				// 0이 들어가면 넘어간다.
				if (num % 10 == 0 || num % 100 < 10) continue;
				// 서로 다른 숫자로만 이루어진 게 아니면 넘어간다.
				if (!isUnique(num)) continue;
				if (strikeCount(num, q) == s && ballCount(num, q) == b) {
					myList.push_back(num);
				}
			}
		}
		// 선처리가 된 상태라면
		else {
			// 조건과 맞지 않으면 지운다.
			for (auto it = myList.begin(); it != myList.end(); it++) {
				if (strikeCount(*it, q) == s && ballCount(*it, q) == b) continue;
				myList.erase(it--);
			}
		}
	}

	cout << myList.size();
}
