#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int d, n;
    cin >> d >> n;

    vector<int> minWidth(d);
    int width = 1e10;
    for (int i = 0; i < d; i++) {
        int w;
        cin >> w;
        minWidth[i] = (width = min(width, w));
    }

    vector<int> pizza(n);
    for (int i = 0; i < n; i++) {
        cin >> pizza[i];
    }

    int end = 0;
    for (int i = 0; i < n; i++) {
        if (!i) {
            while (minWidth[end] >= pizza[i]) ++end;

            if (end < n - 1) {
                cout << 0;
                break;
            }
            else if (i == n - 1) {
                cout << end;
                break;
            }

            end -= 2;
        }
        else {
            while (end >= 0 && minWidth[end] < pizza[i]) --end;

            if (end < n - i - 1) {
                cout << 0;
                break;
            }
            else if (i == n - 1) {
                cout << end + 1;
                break;
            }
            
            end--;
        }
    }

    return 0;
}
