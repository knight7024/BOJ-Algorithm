#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Tree {
	int y, x;
	int age = 1;
	Tree() {}
	Tree(int y, int x): y(y), x(x) {}
	Tree(int y, int x, int age): y(y), x(x), age(age) {}
	bool operator<(Tree a) { return age < a.age; }
};

const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int hashCoor(int r, int c) {
    return r * 10 + c;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    int a[10][10];
    int nourish[10][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            // 가장 처음에 양분은 모든 칸에 5만큼 들어있다.
            nourish[i][j] = 5;
        }
    }

    vector<vector<Tree>> adj(110);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        adj[hashCoor(x - 1, y - 1)].emplace_back(x - 1, y - 1, z);
    }

    vector<Tree> aliveTree;
    vector<Tree> deadTree;
    // k년 동안 시뮬레이션
    while (k--) {
        // 봄
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i].empty()) continue;
            sort(adj[i].begin(), adj[i].end());
            // 하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다.
            for (auto & tree: adj[i]) {
                // 자신의 나이만큼 양분을 먹을 수 없는 나무는 즉시 죽는다.
                if (tree.age > nourish[tree.y][tree.x]) {
                    deadTree.emplace_back(tree);
                    continue;
                }
                // 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다.
                nourish[tree.y][tree.x] -= tree.age++;
                aliveTree.emplace_back(tree);
            }
            adj[i].clear();
        }
        // 여름
        for (auto & tree: aliveTree) {
            adj[hashCoor(tree.y, tree.x)].emplace_back(tree);
        }
        aliveTree.clear();
        for (auto & tree: deadTree) {
            // 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다.
            nourish[tree.y][tree.x] += tree.age >> 1;
        }
        deadTree.clear();
        // 가을
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i].empty()) continue;
            // 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무가 생긴다.
            for (auto & tree: adj[i]) {
                if (tree.age % 5) continue;
                for (int j = 0; j < 8; j++) {
                    int nx = tree.x + dx[j];
                    int ny = tree.y + dy[j];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                    adj[hashCoor(ny, nx)].emplace_back(ny, nx);
                }
            }
        }
        // 겨울
        // S2D2가 땅을 돌아다니면서 땅에 양분을 추가한다.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                nourish[i][j] += a[i][j];
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < adj.size(); i++) {
        answer += adj[i].size();
    }

    cout << answer;

    return 0;
}
