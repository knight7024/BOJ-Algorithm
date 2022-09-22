#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int INF = 0x7f7f7f7f;

struct Model {
    int e, h, d, t;
    Model();
    Model(int e, int h, int d, int t): e(e), h(h), d(d), t(t) {}
};

int n;
vector<Model> v;

int dijkstra(int r, int d) {
    int dp[2001];
    memset(dp, INF, sizeof dp);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dp[r] = 0;
    pq.emplace(0, r);

    while (!pq.empty()) {
        auto [nowTime, nowHeight] = pq.top();
        pq.pop();
        if (nowHeight == d) break;

        for (int i = 0; nowHeight + v[i].h - v[i].e <= n and i < v.size(); i++) {
            int nextHeight = nowHeight + v[i].d;
            int nextTime = nowTime + v[i].t;
            if (nowHeight < v[i].e or dp[nextHeight] <= nextTime) continue;

            dp[nextHeight] = nextTime;
            pq.emplace(nextTime, nextHeight);
        }
    }

    return dp[d];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    int r, d;
    cin >> r >> d;

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int h, t, e1, e2;
        cin >> h >> t >> e1 >> e2;
        v.emplace_back(e1, h, e2 - e1, t);
        v.emplace_back(e2, h, e1 - e2, t);
    }

    sort(v.begin(), v.end(), [&](Model& a, Model& b) {
        return a.h - a.e < b.h - b.e;
    });

    int answer = dijkstra(r, d);
    cout << (answer == INF ? -1 : answer);

    return 0;
}
