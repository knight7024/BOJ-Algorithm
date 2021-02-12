#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Customer {
	int id;
	long w;
	int counterNum;
	Customer() {}
	Customer(int id, long w): id(id), w(w) {}
	Customer(int id, long w, int counterNum): id(id), w(w), counterNum(counterNum) {}
};

struct cmpC {
	bool operator()(Customer a, Customer b) {
		if (a.w == b.w) return a.counterNum > b.counterNum;
		return a.w > b.w;
	}
};

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	vector<Customer> input(n);
	for (int i = 0; i < n; i++) {
		cin >> input[i].id >> input[i].w;
	}

	priority_queue<Customer, vector<Customer>, cmpC> pq;
	// 먼저 N명 또는 K명을 계산대에 할당한다.
	int i = 0;
	long nowTime = 0;
	for (; i < n && i < k; i++) {
		pq.emplace(input[i].id, input[i].w, i);
	}

	priority_queue<pair<int, int>> line;
	long answer = 0;
	int order = 1;
	while (!pq.empty()) {
		nowTime = pq.top().w;
		// 현재 시간으로 비교해서 이미 끝난 손님들은 뺀다.
		while (!pq.empty() && pq.top().w <= nowTime) {
			line.emplace(pq.top().counterNum, pq.top().id);
			// 손님이 빠지는 계산대에 새로운 손님 할당한다.
			if (i < n) pq.emplace(input[i].id, input[i].w + nowTime, pq.top().counterNum);
			pq.pop();
			i++;
		}
		while (!line.empty()) {
			answer += (long) order++ * line.top().second;
			line.pop();
		}
	}

	cout << answer;

	return 0;
}
