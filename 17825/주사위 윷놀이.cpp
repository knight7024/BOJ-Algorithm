#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#define PIECE 4
#define TURN 10
#define DESTINY 21
using namespace std;

struct Node {
	int next;
	bool canJump = false;
	Node() {}
	Node(int next, bool canJump): next(next), canJump(canJump) {}
};

vector<vector<Node>> map;
int score[] {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0, 13, 16, 19, 25, 22, 24, 28, 27, 26, 30, 35};
vector<int> order;
int position[PIECE];
int answer;

vector<int> predictDest(int p, int dist) {
	vector<int> dest;
	// <현재 위치, 더 이동할 수 있는 횟수, 움직이는 중인지 여부>
	queue<tuple<int, int, bool>> bfs;
	bfs.emplace(position[p], dist, 0);
	while (!bfs.empty()) {
		int nowNode, remainDist; bool isMoving;
		tie(nowNode, remainDist, isMoving) = bfs.front();
		bfs.pop();
		
		// 더 이동할 수 없다면 예상 도착 위치이다.
		if (!remainDist || nowNode == DESTINY) {
			dest.push_back(nowNode);
			continue;
		}

		for (auto& i : map[nowNode]) {
			// 파란색 칸에서 시작하면 파란색 화살표만 타고
			if (!isMoving && (nowNode == 5 || nowNode == 10 || nowNode == 15)) {
				if (!i.canJump) continue;
				bfs.emplace(i.next, remainDist - 1, 1);
			}
			else {
				if (i.canJump) continue;
				bfs.emplace(i.next, remainDist - 1, 1);
			}
		}
	}

	return dest;
}

void playGame(int idx, int nowScore) {
	if (idx >= TURN) {
		answer = max(answer, nowScore);
		return;
	}

	for (int i = 0; i < PIECE; i++) {
		if (position[i] == DESTINY) continue;
		vector<int> result = predictDest(i, order[idx]);
		for (int resultPos : result) {
			bool dupFlag = false;
			for (int j = 0; j < PIECE; j++) {
				if (i == j || position[j] == DESTINY) continue;
				if (position[j] == resultPos) {
					dupFlag = true;
					break;
				}
			}
			if (dupFlag) continue;
			int prevPos = position[i];
			position[i] = resultPos;
			playGame(idx + 1, nowScore + score[resultPos]);
			position[i] = prevPos;
		}
	}
}

int main() {
	// 주사위에서 나올 수 10개: 10개의 턴
	order.resize(TURN);
	for (int i = 0; i < TURN; i++) {
		cin >> order[i];
	}

	// 윷놀이판 전처리
	map.resize(35);
	map[0].emplace_back(1, 0);
	map[1].emplace_back(2, 0);
	map[2].emplace_back(3, 0);
	map[3].emplace_back(4, 0);
	map[4].emplace_back(5, 0);
	map[5].emplace_back(6, 0);
	map[6].emplace_back(7, 0);
	map[7].emplace_back(8, 0);
	map[8].emplace_back(9, 0);
	map[9].emplace_back(10, 0);
	map[10].emplace_back(11, 0);
	map[11].emplace_back(12, 0);
	map[12].emplace_back(13, 0);
	map[13].emplace_back(14, 0);
	map[14].emplace_back(15, 0);
	map[15].emplace_back(16, 0);
	map[16].emplace_back(17, 0);
	map[17].emplace_back(18, 0);
	map[18].emplace_back(19, 0);
	map[19].emplace_back(20, 0);
	map[20].emplace_back(21, 0);
	// 10번 파란색 화살표부터
	map[5].emplace_back(22, 1);
	map[22].emplace_back(23, 0);
	map[23].emplace_back(24, 0);
	map[24].emplace_back(25, 0);
	// 20번 파란색 화살표부터
	map[10].emplace_back(26, 1);
	map[26].emplace_back(27, 0);
	map[27].emplace_back(25, 0);
	// 30번 파란색 화살표부터
	map[15].emplace_back(28, 1);
	map[28].emplace_back(29, 0);
	map[29].emplace_back(30, 0);
	map[30].emplace_back(25, 0);
	// 25번 빨간색 화살표부터
	map[25].emplace_back(31, 0);
	map[31].emplace_back(32, 0);
	map[32].emplace_back(20, 0);

	playGame(0, 0);

	cout << answer;

	return 0;
}
