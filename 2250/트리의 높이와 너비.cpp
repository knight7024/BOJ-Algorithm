#include <algorithm>
#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;

int nowOrder;
int minOrder[10001];
int maxOrder[10001];
int maxHeight = -1;
bool visited[10001];

struct Node {
	int left;
	int right;
};

Node tree[10001];

void inorder(int rootNode, int height) {
	if (rootNode == -1)
		return;
	maxHeight = max(maxHeight, height);

	inorder(tree[rootNode].left, height + 1);
	++nowOrder;
	minOrder[height] = min(minOrder[height], nowOrder);
	maxOrder[height] = max(maxOrder[height], nowOrder);
	inorder(tree[rootNode].right, height + 1);
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	cin >> n;

	memset(minOrder, 0x3f, sizeof(minOrder));

	int root, s1, s2;
	int maxRoot = -1;
	for (int i = 0; i < n; i++) {
		cin >> root >> s1 >> s2;

		maxRoot = max(maxRoot, root);
		visited[s1] = visited[s2] = true;
		tree[root].left = s1;
		tree[root].right = s2;
	}

	int rootNode;
	for (int i = 1; i <= maxRoot; i++) {
		if (!visited[i]) {
			rootNode = i;
			break;
		}
	}

	inorder(rootNode, 1);

	int w = -1, h = 1;
	for (int i = 1; i <= maxHeight; i++) {
		int diff = maxOrder[i] - minOrder[i] + 1;
		if (w < diff) {
			w = diff;
			h = i;
		}
	}

	cout << h << " " << w;
	return 0;
}
