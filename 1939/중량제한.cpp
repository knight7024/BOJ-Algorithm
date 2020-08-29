#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#define INF 2147483647
#define endl '\n'

using namespace std;

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    
    int N, M;
    cin >> N >> M;
    
    int A, B, C;
    int maxWeight = -1;
    // <다리, 중량제한>
    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        adj[A].push_back(make_pair(B, C));
        adj[B].push_back(make_pair(A, C));
        maxWeight = max(maxWeight, C);
    }

    int from, to;
    // from에서 to로 가야한다.
    cin >> from >> to;

    // <간선, 중량>
    queue<int> q;
    bool visited[100001];
    int left = 1, right = maxWeight, mid;
    int answer = 0;
    while (left <= right) {
        // 오버플로우 방지
        mid = left + (right - left) / 2;
        
        // 방문 체크 배열 초기화
        memset(visited, 0, sizeof(visited));
        q.push(from);
        visited[from] = true;
        // BFS 실행
        while (!q.empty()) {
            int front = q.front();
            q.pop();
            
            for (int i = 0; i < adj[front].size(); i++) {
                int next = adj[front][i].first;
                int weight = adj[front][i].second;
                if (!visited[next] && weight >= mid) {
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
        // 이진탐색 결과 처리
        if (!visited[to]) right = mid - 1;
        else left = mid + 1, answer = max(answer, mid);
    }
    cout << answer;
    return 0;
}
