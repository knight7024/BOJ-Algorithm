#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Jewelry {
	long weight;
	long price;
	Jewelry() {}
	Jewelry(long weight, long price): weight(weight), price(price) {}
	bool operator<(Jewelry a) {
		if (weight < a.weight) return true;
		else if (weight == a.weight) return price < a.price;
		return false;
	}
};

struct orderByPrice {
	bool operator()(Jewelry a, Jewelry b) {
		if (a.price < b.price) return true;
		else if (a.price == b.price) return a.weight < b.weight;
		return false;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	vector<Jewelry> info;
	for (int i = 0; i < n; i++) {
		int m, v;
		cin >> m >> v;
		info.emplace_back(m, v);
	}

	vector<long> backpack(k);
	for (int i = 0; i < k; i++) {
		cin >> backpack[i];
	}

	sort(info.begin(), info.end());
	sort(backpack.begin(), backpack.end());

	priority_queue<Jewelry, vector<Jewelry>, orderByPrice> pq;
	int infoIdx = 0;
	long answer = 0;
	for (long i : backpack) {
		for (; infoIdx < info.size(); infoIdx++) {
			if (info[infoIdx].weight > i) break;
			pq.push(info[infoIdx]);
		}
		// 가방에는 '최대' 한 개의 보석만 넣을 수 있다.
		// 무게가 중복되는 가방의 경우에는 큐가 비어있을 수 있다.
		if (pq.empty()) continue;
		answer += pq.top().price;
		pq.pop();
	}

	cout << answer;

	return 0;
}
