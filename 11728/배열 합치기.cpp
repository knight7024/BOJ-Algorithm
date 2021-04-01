#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int n, m;
	cin >> n >> m;
	
	vector<int> arr1(n);
	for (int i = 0; i< n; i++) {
		cin >> arr1[i];
	}
	
	sort(arr1.begin(), arr1.end());
	
	vector<int> arr2(m);
	for (int i = 0; i < m; i++) {
		cin >> arr2[i];
	}
	
	sort(arr2.begin(), arr2.end());
	
	int i = 0, j = 0;
	while (i < n || j < m) {
		if (i >= n || j >= m) {
			if (i >= n) cout << arr2[j++] << ' ';
			else if (j >= m) cout << arr1[i++] << ' ';
			continue;
		}
		
		if (arr1[i] > arr2[j]) cout << arr2[j++] << ' ';
		else cout << arr1[i++] << ' ';
	}
	
	return 0;
}
