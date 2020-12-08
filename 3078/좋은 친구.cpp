#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	vector<int> friends;
	for (int i = 0; i < n; i++) {
		string name;
		cin >> name;
		friends.push_back(name.size());
	}

	queue<int> q;
	int num[21] {};
	int idx = 0;
	for (; idx <= k; idx++) {
		q.push(friends[idx]);
		num[friends[idx]]++;
	}

	long answer = 0;
	while (!q.empty()) {
		answer += num[q.front()] - 1;
		num[q.front()]--;
		q.pop();

		if (idx < n) {
			q.push(friends[idx]);
			num[friends[idx]]++;
			idx++;
		}
	}

	cout << answer;
	return 0;
}
