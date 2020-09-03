#include <algorithm>
#include <iostream>
#include <vector>
#define MAX 21
#define endl '\n'

using namespace std;

// 트리 인접 리스트
vector<vector<int>> adj;
// 트리 노드들의 높이
vector<int> height;
// [A][B]: A 노드의 2^B번째 조상
int ancestor[100001][MAX];
// 특정 노드 방문 여부
bool visited[100001];

void dfs(int start, int h) {
	visited[start] = true;
	height[start] = h;

	for (int i = 0; i < adj[start].size(); i++) {
		if (!visited[adj[start][i]]) {
			// 2^0은 1이므로 다음 노드의 바로 이전 조상을 현재 노드로 저장한다.
			ancestor[adj[start][i]][0] = start;
			dfs(adj[start][i], h + 1);
		}
	}
}

int lca(int x, int y) {
	// 높이가 더 큰 노드 구분
	int deeperNode = x, shallowerNode = y;
	if (height[y] > height[x]) {
		deeperNode = y;
		shallowerNode = x;
	}

	// 두 노드 간의 높이 차를 최소로 메꾸기 위해 더 깊이 있는 노드를 위로
	// 끌어올린다. 순차탐색 대신 2^i씩 검사하여 시간복잡도를 줄인다.
	for (int i = MAX - 1; i >= 0; i--) {
		if (height[deeperNode] - height[shallowerNode] >= (1 << i)) {
			deeperNode = ancestor[deeperNode][i];
		}
	}

	// 둘이 같아지면 공통 조상이므로 바로 반환
	if (deeperNode == shallowerNode)
		return deeperNode;

	for (int i = MAX - 1; i >= 0; i--) {
		// 공통 조상 발견 시 종료
		int nextD = ancestor[deeperNode][i];
		int nextS = ancestor[shallowerNode][i];
		if (nextD == nextS) continue;
		deeperNode = nextD;
		shallowerNode = nextS;
	}
	// 발견된 공통 조상 반환
	return ancestor[deeperNode][0];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	adj.resize(n + 1);
	height.resize(n + 1);

	// 인접리스트로 트리 연결
	int a, b;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(1, 0);

	// dp로 노드들의 조상 저장하기
	for (int j = 1; j < MAX; j++) {
		for (int i = 1; i <= n; i++) {
			// 현재 노드인 i의 2^j번째 조상은
			// i의 2^(j-1)번째 조상의 2^(j-1) 조상과 동일하다.
			// ex) 8번째 조상은 4번째 조상의 4번째 조상이다.
			// 2^j = 2^(j-1) + 2^(j-1) 이기 때문.
			ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
		}
	}

	int m;
	cin >> m;

	int x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		cout << lca(x, y) << endl;
	}
	return 0;
}
