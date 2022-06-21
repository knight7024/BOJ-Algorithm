#include <bits/stdc++.h>
using namespace std;

int parent[100001];

int findParent(int n) {
    if (parent[n] == -1) return n;
    return parent[n] = findParent(parent[n]);
}

void unionParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a < b) parent[b] = a;
    else parent[a] = b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int g;
    cin >> g;

    int p;
    cin >> p;

    memset(parent, -1, sizeof(parent));

    int answer = 0;
    bool closed = false;
    for (int i = 0; i < p; i++) {
        int x;
        cin >> x;
        if (closed) continue;

        int pos = findParent(x);
        while (parent[pos] != -1) pos = findParent(pos);
        if (!pos) {
            closed = true;
            continue;
        }
        parent[pos] = pos - 1;
        answer++;
    }

    cout << answer;
    
    return 0;
}
