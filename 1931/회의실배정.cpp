#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;

	vector<pair<int, int>> times;
	int start, end;
	for (int i = 0; i < n; i++) {
		cin >> start >> end;
		times.push_back({end, start});
	}
	sort(times.begin(), times.end());

	end = times[0].first;
	int answer = 0;
	for (int i = 1; i < n; i++) {
		if (times[i].second < end) continue;
		end = times[i].first;
		answer++;
	}
	cout << answer + 1;
	return 0;
}
