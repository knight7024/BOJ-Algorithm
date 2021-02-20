#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, l, r;
	cin >> n >> l >> r;

	int ground[50][50];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> ground[i][j];
		}
	}

	queue<pair<int, int>> bfs;
	queue<pair<int, int>> temp;
	bool visited[50][50];

	int answer = 0;
	while (1) {
		bool exitFlag = true;
		memset(visited, 0, sizeof(visited));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j]) continue;
				bfs.emplace(i, j);
				visited[i][j] = true;

				int sum = 0;
				int count = 0;
				while (!bfs.empty()) {
					auto front = bfs.front();
					bfs.pop();
					temp.emplace(front);
					sum += ground[front.first][front.second];
					count++;

					for (int i = 0; i < 4; i++) {
						int nx = dx[i] + front.second;
						int ny = dy[i] + front.first;
						if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
						if (visited[ny][nx]) continue;

						int diff = abs(ground[ny][nx] - ground[front.first][front.second]);
						if (diff >= l && diff <= r) {
							bfs.emplace(ny, nx);
							visited[ny][nx] = true;
						}
					}
				}

				if (count > 1) {
					exitFlag = false;

					while (!temp.empty()) {
						auto front = temp.front();
						temp.pop();
						ground[front.first][front.second] = sum / count;
					}
				}
				else {
					while (!temp.empty()) {
						temp.pop();
					}
				}
			}
		}

		if (exitFlag) break;
		else answer++;
	}

	cout << answer;

	return 0;
}
