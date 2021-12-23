#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

string num2Str[] = {
    "ZERO",
    "ONE",
    "TWO",
    "THREE",
    "FOUR",
    "FIVE",
    "SIX",
    "SEVEN",
    "EIGHT",
    "NINE"
};
string ops = "+-x/=";

string calculate(string& convert) {
    int n = convert.size();
    long result = 0;
    int opsType = 0;
    for (int i = 0; i < n; i++) {
        long num = 0;
        while (i < n && isdigit(convert[i])) {
            num = num * 10 + (convert[i] - '0');
            i++;
        }

        switch (opsType) {
            case 0:
            result += num;
            break;
            
            case 1:
            result -= num;
            break;

            case 2:
            result *= num;
            break;

            case 3:
            result /= num;
            break;
        }

        opsType = ops.find(convert[i]);
    }

    bool minusFlag = false;
    string ret;
    if (result < 0) minusFlag = true, result *= -1;
    else if (!result) return "ZERO";
    while (result) {
        ret = num2Str[result % 10] + ret;
        result /= 10;
    }

    return minusFlag ? "-" + ret : ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    int n = s.size();
    string convert;
    for (int i = 0; s[i]; i++) {
        if (s[i] == 'Z') {
            bool isValid = true;
            for (int j = 0; num2Str[0][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[0][j]) {
                    isValid = false;
                    break;
                }
            }
            if (!isValid) {
                cout << "Madness!";
                exit(0);
            }
            convert.push_back('0');
            i += num2Str[0].size() - 1;
        }
        else if (s[i] == 'O') {
            bool isValid = true;
            for (int j = 0; num2Str[1][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[1][j]) {
                    isValid = false;
                    break;
                }
            }
            if (!isValid) {
                cout << "Madness!";
                exit(0);
            }
            convert.push_back('1');
            i += num2Str[1].size() - 1;
        }
        else if (s[i] == 'T') {
            bool isValid = true;
            for (int j = 0; num2Str[2][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[2][j]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                convert.push_back('2');
                i += num2Str[2].size() - 1;
                continue;
            }

            isValid = true;
            for (int j = 0; num2Str[3][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[3][j]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                convert.push_back('3');
                i += num2Str[3].size() - 1;
                continue;
            }

            cout << "Madness!";
            exit(0);
        }
        else if (s[i] == 'F') {
            bool isValid = true;
            for (int j = 0; num2Str[4][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[4][j]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                convert.push_back('4');
                i += num2Str[4].size() - 1;
                continue;
            }

            isValid = true;
            for (int j = 0; num2Str[5][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[5][j]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                convert.push_back('5');
                i += num2Str[5].size() - 1;
                continue;
            }

            cout << "Madness!";
            exit(0);
        }
        else if (s[i] == 'S') {
            bool isValid = true;
            for (int j = 0; num2Str[6][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[6][j]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                convert.push_back('6');
                i += num2Str[6].size() - 1;
                continue;
            }

            isValid = true;
            for (int j = 0; num2Str[7][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[7][j]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                convert.push_back('7');
                i += num2Str[7].size() - 1;
                continue;
            }

            cout << "Madness!";
            exit(0);
        }
        else if (s[i] == 'E') {
            bool isValid = true;
            for (int j = 0; num2Str[8][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[8][j]) {
                    isValid = false;
                    break;
                }
            }
            if (!isValid) {
                cout << "Madness!";
                exit(0);
            }
            convert.push_back('8');
            i += num2Str[8].size() - 1;
        }
        else if (s[i] == 'N') {
            bool isValid = true;
            for (int j = 0; num2Str[9][j]; j++) {
                if (i + j >= n || s[i + j] != num2Str[9][j]) {
                    isValid = false;
                    break;
                }
            }
            if (!isValid) {
                cout << "Madness!";
                exit(0);
            }
            convert.push_back('9');
            i += num2Str[9].size() - 1;
        }
        else {
            if (ops.find(s[i]) == string::npos || ops.find(convert.back()) != string::npos) {
                cout << "Madness!";
                exit(0);
            }
            convert.push_back(s[i]);
        }
    }

    cout << convert << endl << calculate(convert);

    return 0;
}
