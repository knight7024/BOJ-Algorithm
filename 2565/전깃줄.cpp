#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<pair<int, int>> elec;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		elec.emplace_back(a, b);
	}

	sort(elec.begin(), elec.end());

	vector<int> dp;
	dp.push_back(-1);
	for (int i = 0; i < n; i++) {
		if (elec[i].second > dp.back()) dp.push_back(elec[i].second);
		else *lower_bound(dp.begin(), dp.end(), elec[i].second) = elec[i].second;
	}
	
	cout << n - dp.size() + 1;
	return 0;
}
