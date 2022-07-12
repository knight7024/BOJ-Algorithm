#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const long MAX = 1e15;

unordered_map<string, string> numTable {
    {"ONE", "1"}, {"TWO", "2"}, {"THREE", "3"}, {"FOUR", "4"}, {"FIVE", "5"},
    {"SIX", "6"}, {"SEVEN", "7"}, {"EIGHT", "8"}, {"NINE", "9"}, {"ZERO", "0"},
};
string strTable[] {
    "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    string eq; string w;
    for (char& c : s) {
        if (!isupper(c)) {
            if (!w.empty()) {
                cout << "Madness!";
                return 0;
            }
            eq += c;
            continue;
        }
        w += c;
        if (!numTable.count(w)) continue;
        eq += numTable[w];
        w.clear();
    }

    auto eq2Num = [&](string& eq) -> long {
        long ret = 0; long src = 0;
        char op = -1;
        for (int i = 0; eq[i]; i++) {
            if (isupper(eq[i])) return MAX + 1;
            if (isdigit(eq[i])) {
                src = src * 10 + (eq[i] - '0');
                continue;
            }
            if (!isdigit(eq[i - 1])) return MAX + 1;

            if (op == '+') ret += src;
            else if (op == '-') ret -= src;
            else if (op == 'x') ret *= src;
            else if (op == '/') ret /= src;
            else ret = src;
            src = 0;
            op = eq[i];
        }
        
        return ret;
    };
    
    long result = eq2Num(eq);
    if (result > MAX) {
        cout << "Madness!";
        return 0;
    }
    
    cout << eq << endl;
    if (result < 0) {
        cout << '-';
        result *= -1;
    }
    else if (!result) {
        cout << "ZERO";
        return 0;
    }

    stack<string> numStr;
    while (result) {
        numStr.push(strTable[result % 10]);
        result /= 10;
    }
    while (!numStr.empty()) {
        cout << numStr.top();
        numStr.pop();
    }
    
    return 0;
}
