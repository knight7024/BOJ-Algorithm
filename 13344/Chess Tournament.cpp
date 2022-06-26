#include <bits/stdc++.h>
using namespace std;

struct Match {
    int left, right;
    char symbol;
    Match() {}
    Match(int left, int right, char symbol): left(left), right(right), symbol(symbol) {}
    bool operator<(const Match& a) const {
        if (left == a.left) return right < a.right;
        return left < a.left;
    }
};

int parent[50001];
int indegree[50001];

int findParent(int x) {
    if (parent[x] == -1) return x;
    return parent[x] = findParent(parent[x]);
}

void unionParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a < b) parent[b] = a;
    else if (a > b) parent[a] = b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<Match> arr;
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < m; i++) {
        int k, l; char s;
        cin >> k >> s >> l;
        if (s == '=') unionParent(k, l);
        else arr.emplace_back(k, l, s);
    }

    vector<vector<int>> adj(n);
    for (auto& match : arr) {
        int k = findParent(match.left), l = findParent(match.right);
        adj[l].push_back(k);
        indegree[k]++;
    }

    queue<int> bfs;
    bool visited[50001] {};
    for (int i = 0; i < n; i++) {
        int nowParent = findParent(i);
        if (!indegree[nowParent] and !visited[nowParent]) {
            bfs.push(nowParent);
            visited[nowParent] = true;
        }
    }

    bool isCheating = false;
    while (!bfs.empty()) {
        int front = bfs.front();
        bfs.pop();

        for (int next : adj[front]) {
            if (!--indegree[next]) {
                bfs.push(next);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int nowParent = findParent(i);
        if (indegree[nowParent]) {
            isCheating = true;
            break;
        }
    }

    cout << (isCheating ? "inconsistent" : "consistent");
    
    return 0;
}
