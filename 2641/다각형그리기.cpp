#include <iostream>
#include <vector>
#define endl '\n'

using namespace std;

int n;
int dic[] = { 0, 3, 4, 1, 2 };

bool isSameShape(int original[], int reversed[], int target[]) {
	int idx = 0;
	while (idx < n) {
		int count = 0;
		for (int i = idx; count < n; ++i %= n, count++) {
			if (original[count] != target[i] && reversed[count] != target[i]) break;
		}
		if (count == n) return true;
		idx++;
	}
	return false;
}

int main() {
	cin >> n;

	int original[51];
	int reversed[51];

	for (int i = 0; i < n; i++) {
		cin >> original[i];
	}
	for (int i = 0; i < n; i++) {
		reversed[i] = dic[original[n - i - 1]];
	}

	int m;
	cin >> m;

	int dim[101][51];
	vector<int> ans;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> dim[i][j];
		}
		if (isSameShape(original, reversed, dim[i])) {
			ans.push_back(i);
		}
	}

	cout << ans.size() << endl;
	for (int a : ans) {
		for (int i = 0; i < n; i++) cout << dim[a][i] << " ";
		cout << endl;
	}
	return 0;
}
