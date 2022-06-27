#include <bits/stdc++.h>
using namespace std;

const vector<int> valueArr {1, 1, 2, 3, 4, 5, 9, 10, 20, 30, 40, 50, 90, 100, 200, 300, 400, 500, 900, 1000, 2000, 3000};
const vector<string> symbolArr {"", "I", "II", "III", "IV", "V", "IX", "X", "XX", "XXX", "XL", "L", "XC", "C", "CC", "CCC", "CD", "D", "CM", "M", "MM", "MMM"};

unordered_map<string, int> rome2ArabMap;

int rome2Arab(string& rome) {
    int ret = 0;
    string s;
    for (char c : rome) {
        s += c;
        if (!rome2ArabMap.count(s)) {
            s.pop_back();
            ret += rome2ArabMap[s];
            s.clear();
            s += c;
        }
    }
    if (!s.empty()) ret += rome2ArabMap[s];
    return ret;
}

string arab2Rome(int arab) {
    string ret;
    while (arab) {
        for (int i = valueArr.size() - 1; i > 0; i--) {
            if (valueArr[i] > arab) continue;
            ret += symbolArr[i];
            arab -= valueArr[i];
        }
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string a, b;
    cin >> a >> b;

    for (int i = 1; i < valueArr.size(); i++) rome2ArabMap[symbolArr[i]] = valueArr[i];

    int result = rome2Arab(a) + rome2Arab(b);
    cout << result << ' ' << arab2Rome(result);
    
    return 0;
}
