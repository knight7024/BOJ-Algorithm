#include <iostream>
#include <tuple>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define endl '\n'
using namespace std;

typedef tuple<int, int, int> TUPLE;

const int INF = 0x3f3f3f3f;

int n, m;
int dp[101][10001];

struct Node {
	int nextNode;
	int nextTime;
	int nextCost;
	// bool operator< (Node a) const { return nextDist > a.nextDist; }
};

int dijkstra(int start, vector<vector<Node>>& adj) {
	queue<TUPLE> q;
	memset(dp, INF, sizeof(dp));
	q.emplace(0, 0, start);
	
    int minTime = INF;
	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		int nowTime, nowCost, nowNode;
		tie(nowTime, nowCost, nowNode) = front;
		
        if (dp[nowNode][nowCost] < nowTime) continue;
		if (nowNode == n) {
            minTime = min(minTime, nowTime);
            continue;
        }

		for (auto& v : adj[nowNode]) {
			int nextNode = v.nextNode;
			int nextTime = nowTime + v.nextTime;
			int nextCost = nowCost + v.nextCost;
			if (nextCost > m || dp[nextNode][nextCost] <= nextTime) continue;
            dp[nextNode][nextCost] = nextTime;
            q.emplace(nextTime, nextCost, nextNode);
		}
	}
	return minTime;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--) {
		int k;
		cin >> n >> m >> k;

		vector<vector<Node>> adj(n + 1);
		for (int i = 0; i < k; i++) {
			int u, v, c, d;
			cin >> u >> v >> c >> d;
			adj[u].push_back({v, d, c});
		}

		int result = dijkstra(1, adj);
		if (result == INF) cout << "Poor KCM" << endl;
		else cout << result << endl;
	}
	return 0;
}
