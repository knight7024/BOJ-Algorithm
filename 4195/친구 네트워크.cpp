#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

vector<int> parent;
vector<int> childs(200000);

void setParent(int n) {
    for (int i = 0; i < n; i++) parent.push_back(i);
}

int getParent(int node) {
    if (parent[node] == node) return node;
    return parent[node] = getParent(parent[node]);
}

void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a > b) parent[a] = b, childs[b] += childs[a] + 1;
    else parent[b] = a, childs[a] += childs[b] + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        int f;
        cin >> f;
        parent.clear(); setParent(200000);
        fill(childs.begin(), childs.end(), 0);

        unordered_map<string, int> hash;
        int idx = 0;
        for (int i = 0; i < f; i++) {
            string name1, name2;
            cin >> name1 >> name2;

            if (!hash.count(name1)) hash[name1] = idx++;
            if (!hash.count(name2)) hash[name2] = idx++;
            
            if (getParent(hash[name1]) == getParent(hash[name2])) {
                cout << childs[getParent(hash[name1])] + 1 << endl;
            }
            else {
                unionParent(hash[name1], hash[name2]);
                cout << childs[getParent(hash[name1])] + 1 << endl;
            }
        }
    }

    return 0;
}
