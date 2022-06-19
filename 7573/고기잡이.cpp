#include <bits/stdc++.h>
using namespace std;

int n, l, m;
vector<pair<int, int>> fishes;

int countFishes(int y, int x, int w, int h) {
    int ret = 0;
    for (int boundY = y - h; boundY <= y; boundY++) {
        for (int boundX = x - w; boundX <= x; boundX++) {
            int count = 0;
            for (int i = 0; i < m; i++) {
                if (boundX + w >= fishes[i].second and fishes[i].second >= boundX
                    and boundY + h >= fishes[i].first and fishes[i].first >= boundY) count++;
            }
            ret = max(ret, count);
        }
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> l >> m;

    fishes.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> fishes[i].first >> fishes[i].second;
    }

    vector<int> divNum;
    for (int i = 1; i * 2 <= l / 2; i++) {
        divNum.push_back(i);
        if (i != l / 2 - i) divNum.push_back(l / 2 - i);
    }

    int answer = 0;
    for (int w : divNum) {
        int h = l / 2 - w;
        for (int i = 0; i < m; i++) {
            answer = max(answer, countFishes(fishes[i].first, fishes[i].second, w, h));
        }
    }

    cout << answer;
    
    return 0;
}
