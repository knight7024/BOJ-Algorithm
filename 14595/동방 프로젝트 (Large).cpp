#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int parent[1000001];

int getParent(int x) {
    if (parent[x] == -1) return x;
    return parent[x] = getParent(parent[x]);
}

void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a > b) parent[b] = a;
    else if (a < b) parent[a] = b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    memset(parent, -1, sizeof parent);
    while (m--) {
        int x, y;
        cin >> x >> y;
        for (int i = x; i <= y; i++) {
            int iParent = getParent(i);
            unionParent(i, x);
            if (iParent != i) {
                i = iParent - 1;
                continue;
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        answer += getParent(i) == i;
    }

    cout << answer;

    return 0;
}
