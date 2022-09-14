#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int convertTime(string t) {
    int h = stoi(t.substr(0, 2));
    int m = stoi(t.substr(3, 2));
    return h * 60 + m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    while (n--) {
        string s; int d;
        cin >> s >> d;

        int start = convertTime(s);
        int lastDay = start + d;

        int answer = 0;
        int m = 0;
        while (start < lastDay) {
            if (start <= convertTime("08:00")) {
                int nowDay = start / 1440;
                if (start + 300 <= min(convertTime("08:00"), lastDay)) {
                    answer += 5000;
                    start = min(convertTime("08:00"), lastDay);
                    continue;
                }
            }
            else { 
                int nowDay = start / 1440 * 1440;
                int nextDay = nowDay + 1440;
                if (start >= nowDay + convertTime("22:00") and start + 300 <= min(nextDay + convertTime("08:00"), lastDay)) {
                    answer += 5000;
                    start = min(nextDay + convertTime("08:00"), lastDay);
                    m = 0;
                    continue;
                }
            }
            start += 1; answer += m ? 0: 1000; ++m %= 60;
        }

        cout << answer << endl;
    }

    return 0;
}
