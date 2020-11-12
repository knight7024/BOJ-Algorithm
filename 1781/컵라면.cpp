#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;

	vector<pair<int, int>> list;
	int deadline, cup;
	for (int i = 0; i < n; i++) {
		cin >> deadline >> cup;
		list.push_back({deadline, cup});
	}

	sort(list.begin(), list.end());

	priority_queue<int> pq;

	int totalCup = 0;
	for (int i = 0; i < n; i++) {
		auto& p = list[i];
		if (p.first == 0) continue;

		// 큐의 크기가 문제를 푼 단위 시간이 된다.
		int time = pq.size();
		// 문제를 푼 뒤의 시간이 데드라인보다 작으면
		if (time < p.first) {
			pq.push(-p.second);
			totalCup += p.second;
		}
		// 문제를 푼 뒤의 시간이 데드라인을 넘으면
		else {
			// 현재 문제보다 컵라면 수가 적은 문제를 뺀다.
			if (!pq.empty() && -pq.top() < p.second) {
				totalCup -= -pq.top();
				pq.pop();
				pq.push(-p.second);
				totalCup += p.second;
			}
		}
	}

	cout << totalCup;
	return 0;
}
