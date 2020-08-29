#include <iostream>
#include <stack>
#include <cstring>
#define endl '\n'

using namespace std;

int n;
// 0 미탐색, 1 탐색 중, 2 탐색 완료
int visited[501];
bool isCycle;

void dfs(int start, bool rank[][501], stack<int>& topo) {
	// 현재 노드를 탐색 중인 상태로 변경
	visited[start] = 1;
	for (int i = 1; i <= n; i++) {
		// 간선이 연결되어 있는데,
		if (rank[start][i]) {
			// 미탐색한 노드이면
			if (!visited[i]) {
				dfs(i, rank, topo);
			}
			// 탐색 중인 노드이면 사이클
			else if (visited[i] == 1) {
				isCycle = true;
				return;
			}
		}
	}
	topo.push(start);
	// 탐색 완료
	visited[start] = 2;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    
	int T;
	cin >> T;

	while (T--) {
		cin >> n;

		bool rank[501][501] {};
		int team[501];
		for (int i = 0; i < n; i++) cin >> team[i];

		// 간선 연결
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				rank[team[i]][team[j]] = true;
			}
		}

		int m;
		cin >> m;

		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			// 승패가 뒤바뀌었으니 간선 상태도 뒤집어준다.
			rank[a][b] ^= true;
			rank[b][a] ^= true;
		}		

		stack<int> topo;
		for (int i = 1; i <= n; i++) {
			if (!visited[i]) dfs(i, rank, topo);
			// 사이클이 발견되면 더 탐색할 이유가 없음
			if (isCycle) break;
		}

		if (!isCycle) {
			// 위상정렬
		    while (!topo.empty()) {
			    cout << topo.top() << " ";
			    topo.pop();
		    }
			cout << endl;
		}
		else cout << "IMPOSSIBLE" << endl;

		memset(visited, 0, sizeof(visited));
		isCycle = false;
	}
	return 0;
}
