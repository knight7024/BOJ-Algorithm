#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n;
string ops;
vector<int> prefixSum {0};

bool isValidOps(size_t size) {
	int nextStep = n - 1;
	int nowIdx = size - 1;
	for (int i = 0; i < size; i++) {
		int sum = prefixSum[size] - prefixSum[i];
		if ((ops[nowIdx] == '+' && sum <= 0) || (ops[nowIdx] == '-' && sum >= 0) || (ops[nowIdx] == '0' && sum)) return false;
		nowIdx += nextStep--;
	}

	return true;
}

void backtracking(int idx) {
	if (!idx) {
		for (int i = 1; i <= n; i++) {
			cout << prefixSum[i] - prefixSum[i - 1] << ' ';
		}
		exit(0);
	}

	for (int i = -10; i <= 10; i++) {
		prefixSum.push_back(i + prefixSum.back());
		if (isValidOps(prefixSum.size() - 1)) backtracking(idx - 1);
		prefixSum.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> ops;

	backtracking(n);

	return 0;
}
