#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX 1000

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;


		int x, y;
		vector<pair<int, int>> coor;
		// 상근이네 집
		cin >> x >> y;
		coor.push_back({x, y});
		// 편의점
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			coor.push_back({x, y});
		}
		// 락 페스티벌
		cin >> x >> y;
		coor.push_back({x, y});

		int graph[103][103];
		memset(graph, INF, sizeof(graph));

		// 좌표들 사이의 기본 거리들 저장
		for (int i = 0; i < n + 2; i++) {
			for (int j = i + 1; j < n + 2; j++) {
				graph[i][j] = graph[j][i] = abs(coor[i].first - coor[j].first) + abs(coor[i].second - coor[j].second);
			}
		}

		for (int j = 0; j < n + 2; j++) {
			for (int i = 0; i < n + 2; i++) {
				for (int k = 0; k < n + 2; k++) {
					// 맥주 한 병 당 최대 50미터, 최대 20병이므로 한 번에 1000미터 이동 가능
					if (graph[i][j] <= MAX && graph[j][k] <= MAX) {
						graph[i][k] = min(graph[i][k], graph[j][k]);
					}
				}
			}
		}

		// 집부터 락 페스티벌까지 가는 데 1000미터 이상 가게 된다면 sad, 아니면 happy
		cout << (graph[0][n + 1] > MAX ? "sad\n" : "happy\n");
	}
	return 0;
}
