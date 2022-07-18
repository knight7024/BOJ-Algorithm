#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int parent[100001];
int weightByParent[100001];

int getParent(int x) {
    if (parent[x] == -1) return x;
    int ret = getParent(parent[x]);
    weightByParent[x] += weightByParent[parent[x]];
    return parent[x] = ret;
}

void unionParent(int a, int b, int w) {
    int aParent = getParent(a);
    int bParent = getParent(b);
    parent[aParent] = bParent;
    weightByParent[aParent] = weightByParent[b] + w - weightByParent[a];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    while (cin >> n >> m) {
        if (!n and !m) break;
        memset(parent, -1, sizeof parent);
        memset(weightByParent, 0, sizeof weightByParent);
        while (m--) {
            char q; int a, b;
            cin >> q >> a >> b;

            if (q == '!') {
                int w;
                cin >> w;
                if (getParent(a) == getParent(b)) continue;
                unionParent(a, b, w);
            }
            else {
                if (getParent(a) != getParent(b)) {
                    cout << "UNKNOWN" << endl;
                    continue;
                }
                cout << weightByParent[a] - weightByParent[b] << endl;
            }
        }
    }
    
    return 0;
}
