#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#define endl '\n'
using namespace std;

string charSet[] = {"a", "b", "k", "d", "e", "g", "h", "i", "l", "m", "n", "ng", "o", "p", "r", "s", "t", "u", "w", "y"};

unordered_map<string, int> dic;

bool cmp(string & a, string & b) {
    int aCursor = 0, bCursor = 0;
    while (aCursor < a.size() && bCursor < b.size()) {
        // n과 ng 분리하는 전처리
        bool isNgA = false;
        if (aCursor < a.size() - 1 && a[aCursor] == 'n' && a[aCursor + 1] == 'g') {
            isNgA = true;
            aCursor += 2;
        }

        bool isNgB = false;
        if (bCursor < b.size() - 1 && b[bCursor] == 'n' && b[bCursor + 1] == 'g') {
            isNgB = true;
            bCursor += 2;
        }

        // 같은 문자일 때,
        if (isNgA && isNgA == isNgB) continue;
        if (!isNgA && !isNgB && a[aCursor] == b[bCursor]) {
            aCursor++; bCursor++;
            continue;
        }

        // 다른 문자일 때,
        string aStr; aStr += a[aCursor];
        string bStr; bStr += b[bCursor];
        int aWeight = isNgA ? 11 : dic[aStr], bWeight = isNgB ? 11 : dic[bStr];
        return aWeight < bWeight;
    }

    return a.size() < b.size();
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<string> minsik(n);
	for (int i = 0; i < n; i++) {
		cin >> minsik[i];
	}

	for (int i = 0; i < 20; i++) {
		dic[charSet[i]] = i;
	}

	sort(minsik.begin(), minsik.end(), cmp);

	for (string& s : minsik) cout << s << endl;

	return 0;
}
