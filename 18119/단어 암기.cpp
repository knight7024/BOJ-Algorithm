#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> strToBin;
	vector<int> forgotAlphabet(n, 0);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;

		int bin = 0;
		for (char c : s) {
			bin |= 1 << (c - 'a');
		}

		strToBin.push_back(bin);
	}

	int count = n;
	for (int i = 0; i < m; i++) {
		char o, x;
		cin >> o >> x;

		if (o == '1') {
			// 해당 알파벳의 비트를 0으로
			for (int j = 0; j < n; j++) {
				if (strToBin[j] == (strToBin[j] | (1 << (x - 'a')))) {
					if (!forgotAlphabet[j]) count--;
					forgotAlphabet[j] |= (1 << (x - 'a'));
				}
			}
		}
		else if (o == '2') {
			// 해당 알파벳의 비트를 1로
			for (int j = 0; j < n; j++) {
				if (forgotAlphabet[j] == (forgotAlphabet[j] | (1 << (x - 'a')))) {
					forgotAlphabet[j] &= ~(1 << (x - 'a'));
					if (!forgotAlphabet[j]) count++;
				}
			}
		}
		cout << count << endl;
	}
}
