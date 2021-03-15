#include <iostream>
#include <vector>
#include <algorithm>
#define GAME 7
#define endl '\n'
using namespace std;

const long MOD = 1e9 + 7;

bool cmp(const pair<long, int>& a, const pair<long, int>& b) {
	return a.first < b.first;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<long> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<long> b(m);
	for (int i = 0; i < m; i++) {
		cin >> b[i];
	}

	vector<pair<long, int>> rest(n);
	for (int i = 0; i < n; i++) {
		rest[i].first = a[i] % GAME;
		rest[i].second = i;
	}

	sort(rest.begin(), rest.end());

	bool removed[100001] {};
	bool checked[7] {};
	long sum = 0;
	int countSum = 0;
	for (int i = 0; i < m; i++) {
		sum += b[i];
		if (checked[sum % GAME]) continue;
		// 0이 되는 개수
		auto from = lower_bound(rest.begin(), rest.end(), pair<long, int>((GAME - sum % GAME) % GAME, 0), cmp);
		auto to = upper_bound(rest.begin(), rest.end(), pair<long, int>((GAME - sum % GAME) % GAME, 0), cmp);
		if (removed[(*from).second]) continue;
		if (countSum + to - from == n) {
			sum -= b[i];
			continue;
		}
		countSum += to - from;
		for (auto i = from; i < to; i++) removed[(*i).second] = true;
	}

	cout << n - countSum << endl;
	for (int i = 0; i < n; i++) {
		if (removed[i]) continue;
		cout << (a[i] + sum) % MOD << ' ';
	}

	return 0;
}
