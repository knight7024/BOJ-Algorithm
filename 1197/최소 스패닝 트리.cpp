#include <bits/stdc++.h>
using namespace std;

struct Vertex {
    int u, v;
    int dist;
    Vertex() {}
    Vertex(int u, int v, int dist): u(u), v(v), dist(dist) {};
    bool operator<(const Vertex& a) const { return this->dist > a.dist; }
};

int parent[10001];

int getParent(int n) {
    if (parent[n] == -1) return n;
    return parent[n] = getParent(parent[n]);
}

void setParent(int a, int b) {
    if (a > b) swap(a, b);
    a = getParent(a);
    b = getParent(b);
    parent[b] = a;
}

bool isCyclic(int a, int b) {
    return getParent(a) == getParent(b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int v, e;
    cin >> v >> e;

    memset(parent, -1, sizeof(parent));

    priority_queue<Vertex> pq;
    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        pq.emplace(a, b, c);
    }

    int answer = 0;
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        
        if (!isCyclic(top.u, top.v)) {
            setParent(top.u, top.v);
            answer += top.dist;
        }
    }

    cout << answer;

    return 0;
}
