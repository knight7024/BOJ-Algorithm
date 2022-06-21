#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

struct Log {
    int id;
    int x1, x2, y;
};

int parent[100001];

void makeParent(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
}

int findParent(int n) {
    if (parent[n] == n) return n;
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

    int n, q;
    cin >> n >> q;

    vector<Log> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i].id = i + 1;
        cin >> arr[i].x1 >> arr[i].x2 >> arr[i].y;
    }

    sort(arr.begin(), arr.end(), [&](Log& a, Log& b) {
        if (a.x1 == b.x1) return a.x2 < b.x2;
        return a.x1 < b.x1;
    });

    makeParent(n);

    int to = arr[0].x2;
    int prevId = arr[0].id;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i].x1 <= to) {
            to = max(to, arr[i].x2);
            unionParent(prevId, arr[i].id);
        }
        else {
            to = arr[i].x2;
            prevId = arr[i].id;
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << (findParent(a) == findParent(b)) << endl;
    }
    
    return 0;
}
