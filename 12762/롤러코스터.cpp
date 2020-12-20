#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<int> pillar(n);
	for (int i = 0; i < n; i++) {
		cin >> pillar[i];
	}

	int answer = -1;
	for (int i = 0; i < n; i++) {
		vector<int> lds(1, -1);
		for (int j = i; j >= 0; j--) {
			if (pillar[j] > lds.back()) lds.push_back(pillar[j]);
			else *lower_bound(lds.begin(), lds.end(), pillar[j]) = pillar[j];
		}

		vector<int> lis(1, -1); 
		for (int j = i; j < n; j++) {
			if (pillar[j] > lis.back()) lis.push_back(pillar[j]);
			else *lower_bound(lis.begin(), lis.end(), pillar[j]) = pillar[j];
		}

		int ldsSize = lds.size() - 1, lisSize = lis.size() - 1;
		answer = max(answer, ldsSize + lisSize - 1);
	}

	cout << answer;

	return 0;
}
