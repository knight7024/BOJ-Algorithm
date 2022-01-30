#include <bits/stdc++.h>
using namespace std;

struct Vertex {
    int u, v;
    double dist;
    Vertex() {}
    Vertex(int u, int v, double dist): u(u), v(v), dist(dist) {};
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

double getDistance(pair<double, double>& a, pair<double, double>& b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed;
    cout.precision(2);

    int n;
    cin >> n;

    memset(parent, -1, sizeof(parent));

    vector<pair<double, double>> stars(n);
    for (int i = 0; i < n; i++) {
        cin >> stars[i].first >> stars[i].second;
    }

    priority_queue<Vertex> pq;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            pq.emplace(i, j, getDistance(stars[i], stars[j]));
        }
    }

    double answer = 0;
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
