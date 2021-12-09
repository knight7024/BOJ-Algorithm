#include <bits/stdc++.h>
using namespace std;

const int knightY[] = {-1, 1, -2, 2, -2, 2, -1, 1};
const int knightX[] = {-2, -2, -1, -1, 1, 1, 2, 2};

const int bishopY[] = {-1, 1, -1, 1};
const int bishopX[] = {-1, -1, 1, 1};

const int rookY[] = {-1, 0, 0, 1};
const int rookX[] = {0, -1, 1, 0};

const int INF = 0x7f7f7f7f;

struct Coor {
    int y, x;
    int dist = 0;
    int state = 0;
    Coor() {}
    Coor(int y, int x, int dist, int state): y(y), x(x), dist(dist), state(state) {}
    bool operator==(Coor& a) { return y == a.y && x == a.x; }
    bool operator!=(Coor& a) { return !(*this == a); }
};

struct cmp {
    bool operator()(const Coor &a, const Coor &b) {
        return a.dist >= b.dist;
    }
};

int n, m;
int a, b, c;
int prey[51][51];

int dijkstra(Coor &start) {
    priority_queue<Coor, vector<Coor>, cmp> pq;
    int dist[51][51][1 << 4];
    memset(dist, INF, sizeof(dist));

    pq.emplace(start);
    dist[start.y][start.x][start.state] = start.dist;

    int answer = INF;
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        if (dist[top.y][top.x][top.state] < top.dist) continue;
        if (top.state == (1 << m) - 1) {
            answer = min(answer, top.dist);
            continue;
        }

        // 나이트
        for (int i = 0; i < 8; i++) {
            int ny = top.y + knightY[i];
            int nx = top.x + knightX[i];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
            
            int nextState = prey[ny][nx] ? top.state | 1 << (prey[ny][nx] - 1) : top.state;
            int nextDist = top.dist + a;
            if (dist[ny][nx][nextState] > nextDist) {
                pq.emplace(ny, nx, nextDist, nextState);
                dist[ny][nx][nextState] = nextDist;
            }
        }

        // 비숍
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                int ny = top.y + bishopY[j] * i;
                int nx = top.x + bishopX[j] * i;
                if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
                
                int nextState = prey[ny][nx] ? top.state | 1 << (prey[ny][nx] - 1) : top.state;
                int nextDist = top.dist + b;
                if (dist[ny][nx][nextState] > nextDist) {
                    pq.emplace(ny, nx, nextDist, nextState);
                    dist[ny][nx][nextState] = nextDist;
                }
            }
        }

        // 룩
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                int ny = top.y + rookY[j] * i;
                int nx = top.x + rookX[j] * i;
                if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
                
                int nextState = prey[ny][nx] ? top.state | 1 << (prey[ny][nx] - 1) : top.state;
                int nextDist = top.dist + c;
                if (dist[ny][nx][nextState] > nextDist) {
                    pq.emplace(ny, nx, nextDist, nextState);
                    dist[ny][nx][nextState] = nextDist;
                }
            }
        }
    }

    return answer;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    cin >> a >> b >> c;

    Coor duck;
    cin >> duck.y >> duck.x;

    cin >> m;

    for (int i = 1; i <= m; i++) {
        int y, x;
        cin >> y >> x;
        prey[y][x] = i;
    }

    cout << dijkstra(duck);

    return 0;
}
