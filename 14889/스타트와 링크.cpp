#include <iostream>
#include <algorithm>
#define MAX 987654321
#define START 0
#define LINK 1
using namespace std;

int n;
int synergy[20][20];
bool visited[20];
int answer = MAX;

int getPairSynergy() {
	int teamSynergy[2] {};
	for (int i = 0; i < n - 1; i++) {
		int team = visited[i];
		for (int j = i + 1; j < n; j++) {
			if (visited[j] == team) {
				teamSynergy[team] += synergy[i][j] + synergy[j][i];
			}
		}
	}

	return abs(teamSynergy[START] - teamSynergy[LINK]);
}

void recur(int idx, int depth) {
	// 팀 선정이 끝났을 때
	if (depth == n / 2) {
		answer = min(answer, getPairSynergy());
		return;
	}

	for (int i = idx; i < n; i++) {
		visited[i] = LINK;
		recur(i + 1, depth + 1);
		visited[i] = START;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> synergy[i][j];
		}
	}

	recur(0, 0);

	cout << answer;

	return 0;
}
