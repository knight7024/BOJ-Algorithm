#include <iostream>
#include <queue>
#include <algorithm>
#define root(n,k) ((n-2)/(k)+1) 
#define endl '\n'

using namespace std;

long n, k;
int q;

long lca(long x, long y) {
	long dis = 0;
	if (k == 1) return abs(x - y);
	// 아래에 있는 노드를 위로 올린다.
	while (x != y) {
		if (x < y) swap(x, y);
		x = root(x, k);
		dis++;
	}
	return dis;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k >> q;

	long x, y;
	for (int i = 0; i < q; i++) {
		cin >> x >> y;
		cout << lca(x, y) << endl;
	}
	return 0;
}
