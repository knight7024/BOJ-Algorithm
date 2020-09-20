#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

struct seg {
	int start;
	int end;
};

struct node {
	int left = -1;
	int right = -1;
};

vector<int> inorder;
vector<int> postorder;
vector<pair<seg, seg>> segTree;
vector<node> tree;
int rootCount;

void divide(seg left, seg right) {
	int prevRoot = postorder[rootCount];
	// 오른쪽을 우선으로 하지만 탐색할 대상이 없다면 넘어간다.
	if (right.end - right.start != 0) {
		int root = postorder[--rootCount];
		auto it = find(inorder.begin() + right.start, inorder.begin() + right.end, root);
		if (it != inorder.end()) {
			tree[prevRoot].right = root;
			int rootIdx = distance(inorder.begin(), it);
			segTree[root] = {{right.start, rootIdx}, {rootIdx + 1, right.end}};
			divide(segTree[root].first, segTree[root].second);
		}
	}
	
	// 왼쪽을 그 다음으로 하지만 탐색할 대상이 없다면 넘어간다.
	if (left.end - left.start != 0) {
		int root = postorder[--rootCount];
		auto it = find(inorder.begin() + left.start, inorder.begin() + left.end, root);
		if (it != inorder.end()) {
			tree[prevRoot].left = root;
			int rootIdx = distance(inorder.begin(), it);
			segTree[root] = {{left.start, rootIdx}, {rootIdx + 1, left.end}};
			divide(segTree[root].first, segTree[root].second);
		}
	}
}

void preorder(int node)
{
    cout << node << " ";
    if (tree[node].left != -1) preorder(tree[node].left);
    if (tree[node].right != -1) preorder(tree[node].right);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;

	inorder.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> inorder[i];
	}

	postorder.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> postorder[i];
	}

	segTree.resize(n + 1);
	tree.resize(n + 1);
	int root = postorder[n - 1];
	int rootIdx = distance(inorder.begin(), find(inorder.begin(), inorder.end(), root));
	segTree[root] = {{0, rootIdx}, {rootIdx + 1, n}};
	rootCount = n - 1;

	divide(segTree[root].first, segTree[root].second);
	preorder(root);

	return 0;
}
