#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> row(n + 1), col(n + 1);
    int maxrChoco = 0, maxrPiece = 0;
    int maxcChoco = 0, maxcPiece = 0;
    for (int i = 0; i < q; i++) {
        int t, a;
        cin >> t >> a;

        if (t == 1) {
            ++row[a];
            if (row[a] > maxrChoco) {
                maxrChoco = row[a];
                maxrPiece = 1;
            }
            else if (row[a] == maxrChoco) maxrPiece++;
        }
        else {
            ++col[a];
            if (col[a] > maxcChoco) {
                maxcChoco = col[a];
                maxcPiece = 1;
            }
            else if (col[a] == maxcChoco) maxcPiece++;
        }

        if (!maxrPiece) cout << maxcPiece * n << endl;
        else if (!maxcPiece) cout << maxrPiece * n << endl;
        else cout << maxrPiece * maxcPiece << endl;
    }

    return 0;
}
