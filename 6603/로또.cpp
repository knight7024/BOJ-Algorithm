#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 6
#define endl '\n'
using namespace std;

int k;
vector<int> answer;

void recur(int idx, int depth, vector<int>& nums) {
	if (depth == MAX) {
		for (int i : answer) cout << i << ' ';
		cout << endl;
		return;
	}

	for (int i = idx; i < k; i++) {
		answer.push_back(nums[i]);
		recur(i + 1, depth + 1, nums);
		answer.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while (1) {
		cin >> k;
		if (!k) break;

		vector<int> nums(k);
		for (int i = 0; i < k; i++) {
			cin >> nums[i];
		}

		recur(0, 0, nums);

		cout << endl;
	}


    return 0;
}
