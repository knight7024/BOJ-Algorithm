#include <bits/stdc++.h>
using namespace std;

int parent[1001];

int getParent(int x) {
    if (parent[x] == -1) return x;
    return parent[x] = getParent(parent[x]);
}

void unionParent(int a, int b) {
    a = getParent(a);
    b = getParent(b);
    if (a < b) parent[b] = a;
    else if (a > b) parent[a] = b;
}

struct Coor {
    int x, y;
    Coor() {}
    Coor(int x, int y): x(x), y(y) {}
    bool operator==(Coor& a) { return x == a.x and y == a.y; }
    bool operator!=(Coor& a) { return !(*this == a); }
    bool operator<(Coor& a) {
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
    bool operator<=(Coor& a) { return *this == a or *this < a; }
    bool operator>(Coor& a) { return !(*this <= a); }
    bool operator>=(Coor& a) { return *this == a or *this > a; }
};

int ccw(Coor& p1, Coor& p2, Coor& p3) {
    int op = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
    op -= p1.x * p3.y + p2.x * p1.y + p3.x * p2.y;
    return op > 0 ? 1 : op == 0 ? 0 : -1;
}

struct Line {
    Coor from, to;
    Line() {}
    Line(int x1, int y1, int x2, int y2): from(x1, y1), to(x2, y2) {}
    Line(Coor from, Coor to): from(from), to(to) {}

    bool isOverlapped(Line& a) {
    	int line1Result = ccw(from, to, a.from) * ccw(from, to, a.to);
    	int line2Result = ccw(a.from, a.to, from) * ccw(a.from, a.to, to);
    
    	if (line1Result == 0 and line2Result == 0) {
    		if (from > to) return to <= a.to and a.from <= from;
    		if (a.from > a.to) return from <= a.from and a.to <= to;
    		return from <= a.to and a.from <= to;
    	}
    	return line1Result <= 0 and line2Result <= 0;
    }
};

struct Rect {
    vector<Line> lines;
    Rect() {}
    Rect(int x1, int y1, int x2, int y2) {
        lines.emplace_back(x1, y1, x2, y1);
        lines.emplace_back(x1, y1, x1, y2);
        lines.emplace_back(x2, y2, x1, y2);
        lines.emplace_back(x2, y2, x2, y1);
    }

    bool isOverlapped(Rect& a) {
        for (auto& line1 : lines) {
            for (auto& line2 : a.lines) {
                if (!line1.isOverlapped(line2)) continue;
                return true;
            }
        }
        return false;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<Rect> rects;
    Coor start {0, 0};
    bool overlappedFlag = false;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rects.emplace_back(x1, y1, x2, y2);
        
        if (overlappedFlag) continue;
        for (auto& line : rects[i].lines) {
            if (ccw(line.from, line.to, start)) continue;
            if (start.x >= min(line.from.x, line.to.x) and start.x <= max(line.from.x, line.to.x) and
                start.y >= min(line.from.y, line.to.y) and start.y <= max(line.from.y, line.to.y)) {
                overlappedFlag = true;
                break;
            }
        }
    }

    memset(parent, -1, sizeof parent);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!rects[i].isOverlapped(rects[j])) continue;
            unionParent(i, j);
        }
    }

    unordered_set<int> countSet;
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) continue;
        countSet.emplace(i);
    }

    cout << countSet.size() + !overlappedFlag - 1;
    
    return 0;
}
