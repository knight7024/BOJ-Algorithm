#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	
	queue<tuple<int, int, int>> bfs;
	bool visited[201][201][201] {};
	
	bfs.emplace(0, 0, c);
	visited[0][0][c] = true;
	
	vector<int> answer;
	while (!bfs.empty()) {
		auto front = bfs.front();
		bfs.pop();
		
		int nowA, nowB, nowC;
		tie(nowA, nowB, nowC) = front;
		if (!nowA) answer.push_back(nowC);
		
		// A to B
		if (nowA >= b - nowB && !visited[nowA - b + nowB][b][nowC]) {
			bfs.emplace(nowA - b + nowB, b, nowC);
			visited[nowA - b + nowB][b][nowC] = true;
		}
		if (nowB + nowA <= b && !visited[0][nowB + nowA][nowC]) {
			bfs.emplace(0, nowB + nowA, nowC);
			visited[0][nowB + nowA][nowC] = true;
		}
		// A to C
		if (nowA >= c - nowC && !visited[nowA - c + nowC][nowB][c]) {
			bfs.emplace(nowA - c + nowC, nowB, c);
			visited[nowA - c + nowC][nowB][c] = true;
		}
		if (nowC + nowA <= c && !visited[0][nowB][nowC + nowA]) {
			bfs.emplace(0, nowB, nowC + nowA);
			visited[0][nowB][nowC + nowA] = true;
		}
		// B to A
		if (nowB >= a - nowA && !visited[a][nowB - a + nowA][nowC]) {
			bfs.emplace(a, nowB - a + nowA, nowC);
			visited[a][nowB - a + nowA][nowC] = true;
		}
		if (nowA + nowB <= a && !visited[nowA + nowB][0][nowC]) {
			bfs.emplace(nowA + nowB, 0, nowC);
			visited[nowA + nowB][0][nowC] = true;
		}
		// B to C
		if (nowB >= c - nowC && !visited[nowA][nowB - c + nowC][c]) {
			bfs.emplace(nowA, nowB - c + nowC, c);
			visited[nowA][nowB - c + nowC][c] = true;
		}
		if (nowC + nowB <= c && !visited[nowA][0][nowC + nowB]) {
			bfs.emplace(nowA, 0, nowC + nowB);
			visited[nowA][0][nowC + nowB] = true;
		}
		// C to A
		if (nowC >= a - nowA && !visited[a][nowB][nowC - a + nowA]) {
			bfs.emplace(a, nowB, nowC - a + nowA);
			visited[a][nowB][nowC - a + nowA] = true;
		}
		if (nowA + nowC <= a && !visited[nowA + nowC][nowB][0]) {
			bfs.emplace(nowA + nowC, nowB, 0);
			visited[nowA + nowC][nowB][0] = true;
		}
		// C to B
		if (nowC >= b - nowB && !visited[nowA][b][nowC - b + nowB]) {
			bfs.emplace(nowA, b, nowC - b + nowB);
			visited[nowA][b][nowC - b + nowB] = true;
		}
		if (nowB + nowC <= b && !visited[nowA][nowB + nowC][0]) {
			bfs.emplace(nowA, nowB + nowC, 0);
			visited[nowA][nowB + nowC][0] = true;
		}
	}
	
	sort(answer.begin(), answer.end());
	
	for (int i : answer) cout << i << ' ';
	
	return 0;
}
