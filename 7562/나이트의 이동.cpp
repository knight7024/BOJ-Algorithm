#include <iostream>
#include <queue>
#include <algorithm>
#define endl '\n'
using namespace std;

const int dx[] = {-1, -2, -1, -2, 1, 2, 1, 2};
const int dy[] = {-2, -1, 2, 1, -2, -1, 2, 1};

struct Coor {
	int y, x;
	int count;
	Coor() {}
	Coor(int y, int x, int count): y(y), x(x), count(count) {}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;

	while (t--) {
		int l;
		cin >> l;

		int fromY, fromX;
		cin >> fromY >> fromX;

		int toY, toX;
		cin >> toY >> toX;

		queue<Coor> bfs;
		bool visited[301][301] {};

		bfs.emplace(fromY, fromX, 0);
		visited[fromY][fromX] = true;

		while (!bfs.empty()) {
			auto front = bfs.front();
			bfs.pop();

			if (front.y == toY && front.x == toX) {
				cout << front.count << endl;
				break;
			}

			for (int i = 0; i < 8; i++) {
				int ny = dy[i] + front.y;
				int nx = dx[i] + front.x;
				if (ny >= l || ny < 0 || nx >= l || nx < 0) continue;
				if (visited[ny][nx]) continue;

				bfs.emplace(ny, nx, front.count + 1);
				visited[ny][nx] = true;
			}
		}
	}
	
	return 0;
}
