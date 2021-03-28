#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Employee {
	int id;
	int workDays;
	int hurried;
	int lineNum;
	Employee() {}
	Employee(int id, int workDays, int hurried, int lineNum): id(id), workDays(workDays), hurried(hurried), lineNum(lineNum) {}
	bool operator==(Employee& a) { return id == a.id; }
};

struct Cmp {
	bool operator()(Employee& a, Employee& b) {
		if (a.workDays != b.workDays) return a.workDays < b.workDays;
		if (a.hurried != b.hurried) return a.hurried < b.hurried;
		return a.lineNum > b.lineNum;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<queue<Employee>> line(m);
	priority_queue<Employee, vector<Employee>, Cmp> pq;
	Employee me;
	for (int i = 0; i < n; i++) {
		int d, h;
		cin >> d >> h;
		
		line[i % m].emplace(i, d, h, i % m);
		if (i == k) me = {i, d, h, i % m};
	}
	
	// 첫 선두들 우선순위 큐에 넣는다.
	for (int i = 0; i < m; i++) {
		if (line[i].empty()) continue;
		pq.emplace(line[i].front());
	}
	
	int answer = 0;
	while (!pq.empty()) {
		auto front = pq.top();
		pq.pop();
		
		// 내가 화장실을 사용할 차례라면 반복문을 종료한다.
		if (front == me) break;
		// 아니라면 현재 선두를 제외시키고 다음 선두를 넣는다.
		line[front.lineNum].pop();
		if (!line[front.lineNum].empty()) pq.emplace(line[front.lineNum].front());
		answer++;
	}
	
	cout << answer;
	
	return 0;
}
