#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX 15
using namespace std;

struct Coor {
	int y, x;
	Coor() {}
	Coor(int y, int x): y(y), x(x) {}
};

int n, m, d;
bool board[MAX][MAX];
vector<Coor> enemy;
vector<Coor> archer;
int enemyCount;
int answer;

int getDistance(Coor& from, Coor& to) {
	return abs(from.x - to.x) + abs(from.y - to.y);
}

int moveDown(vector<Coor>& enemyTemp, bool removed[]) {
	// 적은 아래로 한 칸 이동하며, 성이 있는 칸으로 이동한 경우에는 게임에서 제외된다.
	int removeCount = 0;
	for (int i = 0; i < enemyTemp.size(); i++) {
		if (removed[i]) continue;
		if (++enemyTemp[i].y >= n) {
			removed[i] = true;
			removeCount++;
		}
	}

	return removeCount;
}

// 같은 적이 여러 궁수에게 공격당할 수 있다.
int simulation() {
	// 적 위치 배열을 새로 복사하고
	vector<Coor> enemyTemp(enemy);
	vector<int> removedEnemy;
	bool removed[MAX * MAX] {};
	// 시뮬레이션 시작
	int removeCount = 0;
	int moveCount = 0;
	while (enemyCount > removeCount + moveCount) {
		// 궁수가 공격할 적의 위치를 찾는다.
		for (auto& i : archer) {
			int minDist = MAX;
			int minX = MAX;
			int enemyIdx = -1;
			for (int j = 0; j < enemyTemp.size(); j++) {
				if (removed[j]) continue;
				int dist = getDistance(i, enemyTemp[j]);
				// 궁수가 공격하는 적은 거리가 D이하인 적 중에서 가장 가까운 적이고
				if (minDist > dist) {
					minDist = dist;
					minX = enemyTemp[j].x;
					enemyIdx = j;
				}
				// 그러한 적이 여럿일 경우에는 가장 왼쪽에 있는 적을 공격
				else if (minDist == dist && minX > enemyTemp[j].x) {
					minX = enemyTemp[j].x;
					enemyIdx = j;
				}
			}
			// 찾은 적의 거리가 D이하라면 제거한다.
			if (minDist <= d) removedEnemy.push_back(enemyIdx);
		}

		// 제거한 적들 처리
		for (int i : removedEnemy) {
			if (removed[i]) continue;
			removed[i] = true;
			removeCount++;
		}
		removedEnemy.clear();

		// 궁수의 공격이 끝나면, 적이 이동한다.
		moveCount += moveDown(enemyTemp, removed);
	}
	
	return removeCount;
}

// nCr: n개 중에 r개 뽑는다. 다만, n은 열의 수, r은 궁수 3명으로 고정
void combination(int idx, int depth) {
	if (depth == 3) {
		answer = max(answer, simulation());
		return;
	}

	for (int i = idx; i < m; i++) {
		archer.emplace_back(n, i);
		combination(i + 1, depth + 1);
		archer.pop_back();
	}
}

int main() {
	cin >> n >> m >> d;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			if (board[i][j]) {
				enemy.emplace_back(i, j);
				enemyCount++;
			}
		}
	}

	combination(0, 0);
	
	cout << answer;

	return 0;
}
