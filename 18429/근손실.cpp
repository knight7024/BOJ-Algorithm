#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 500
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;

	vector<int> kit(n);
	vector<int> perm;
	for (int i = 0; i < n; i++) {
		cin >> kit[i];
		perm.push_back(i + 1);
	}

	int answer = 0;
	do {
		int weight = MAX;
		bool flag = true;
		for (int i : perm) {
			weight = weight - k + kit[i - 1];
			if (weight < MAX) {
				flag = false;
				break;	
			}
		}
		answer += flag;
	} while (next_permutation(perm.begin(), perm.end()));

	cout << answer;
	
	return 0;
}
