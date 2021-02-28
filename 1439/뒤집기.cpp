#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;

	int zeroCount = 0;
	int oneCount = 0;
	for (int i = 0; s[i]; i++) {
		int j = i;
		while (s[j] == s[i]) j++;
		i = j - 1;
		if (s[i] == '1') oneCount++;
		else zeroCount++;
	}

	cout << min(zeroCount, oneCount);

	return 0;
}
