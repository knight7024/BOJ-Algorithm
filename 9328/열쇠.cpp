#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define endl '\n'

using namespace std;

struct coor {
	int y;
	int x;
};

char map[101][101];
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int h, w;
bool visited[101][101];
int nowDoc;

bool isUpper(char c) {
	return isupper(c);
}

bool init(char item, int y, int x, queue<coor>& q, bool key[], queue<coor> adjKey[]) {
	visited[y][x] = true;
	
	switch (item) {
	// 빈 공간일 때,
	case '.':
		q.push({y, x});
		break;

	// 벽일 때,
	case '*':
		break;

	// 문서일 때,
	case '$':
		++nowDoc;
		q.push({y, x});
		break;

	// 대소문자일 때,
	default:
		// 대문자라면 문
		if (isUpper(item)) {
			if (key[tolower(item) - 'a']) {
				q.push({y, x});
			}
			else {
				adjKey[tolower(item) - 'a'].push({y, x});
				return true;
			}
		}
		// 소문자라면 열쇠
		else {
			key[tolower(item) - 'a'] = true;
			q.push({y, x});
		}
		break;
	}
	return false;
}

bool bfs(int y, int x, bool key[], queue<coor> adjKey[26]) {
	// coor: 다음으로 갈 좌표 저장
	queue<coor> q;

	bool needRetry = init(map[y][x], y, x, q, key, adjKey);
	if (needRetry) return true;
	// BFS 탐색 시작
	while (!q.empty()) {
		auto front = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = front.x + dx[i];
			int ny = front.y + dy[i];
			if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
			if (visited[ny][nx]) continue;

			needRetry |= init(map[ny][nx], ny, nx, q, key, adjKey);
		}
	}
	return needRetry;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin >> T;

	string nowKey;
	while (T--) {
		cin >> h >> w;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
			}
		}

		// 현재 가지고 있는 열쇠들의 소유 여부 체크
		bool key[26]{};
		string nowKey;
		cin >> nowKey;
		if (nowKey != "0") {
			for (char c : nowKey) {
				key[c - 'a'] = true;
			}
		}

		memset(visited, 0, sizeof(visited));
		nowDoc = 0;

		queue<coor> adjKey[26];
		bool needRetry = false;
		// 빌딩 가장자리의 빈 공간이나 문 검사
		for (int i = 0; i < w; i++) {
			// 지도의 맨 윗줄 검사
			if (map[0][i] != '*' && !visited[0][i]) {
				needRetry |= bfs(0, i, key, adjKey);
			}
			// 지도의 맨 아랫줄 검사
			if (map[h - 1][i] != '*' && !visited[h - 1][i]) {
				needRetry |= bfs(h - 1, i, key, adjKey);
			}
		}
		for (int i = 0; i < h; i++) {
			// 중복되는 부분 제외하고 검사
			if (i == 0 || i == h - 1) continue;

			// 지도의 맨 왼쪽줄 검사
			if (map[i][0] != '*' && !visited[i][0]) {
				needRetry |= bfs(i, 0, key, adjKey);				
			}
			// 지도의 맨 오른쪽줄 검사
			if (map[i][w - 1] != '*' && !visited[i][w - 1]) {
				needRetry |= bfs(i, w - 1, key, adjKey);	
			}
		}
		// BFS를 마친 뒤에 획득한 열쇠에 따라 재탐색
		while (needRetry) {
			needRetry = false;
			for (int i = 0; i < 26; i++) {
				if (!key[i]) continue;
				
				while (!adjKey[i].empty()) {
					needRetry = true;
					auto front = adjKey[i].front();
					adjKey[i].pop();

					bfs(front.y, front.x, key, adjKey);
				}
			}
		}
		cout << nowDoc << endl;
	}
	return 0;
}
