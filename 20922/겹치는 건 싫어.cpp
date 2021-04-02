#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int n, k;
	cin >> n >> k;
	
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	int start = 0, end = 0;
	int check[100001] {};
	check[arr[0]] = 1;
	int answer = 0;
	while (start < n) {
		answer = max(answer, end - start + 1);
		if (end >= n - 1) {
			--check[arr[start++]];
			continue;
		}
		if (++check[arr[++end]] > k) {
			--check[arr[end--]];
			--check[arr[start++]];
		}
	}
	
	cout << answer;
	
	return 0;
}
