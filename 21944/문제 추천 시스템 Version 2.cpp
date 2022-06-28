#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

struct Problem {
    int id;
    int difficulty;
    Problem() {}
    Problem(int id, int difficulty): id(id), difficulty(difficulty) {}
    bool operator<(const Problem& a) const {
        if (difficulty == a.difficulty) return id < a.id;
        return difficulty < a.difficulty;
    }
};

set<Problem> rQ[101];
set<Problem> rSet;
int pGroup[100001];
int pDifficulty[100001];
bool isSolved[100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int p, l, g;
        cin >> p >> l >> g;
        rQ[g].emplace(p, l);
        rSet.emplace(p, l);
        pGroup[p] = g;
        pDifficulty[p] = l;
    }

    int m;
    cin >> m;

    string order;
    while (m--) {
        cin >> order;
        if (order[0] == 'a') {
            int p, l, g;
            cin >> p >> l >> g;
            rQ[g].emplace(p, l);
            rSet.emplace(p, l);
            isSolved[p] = false;
            pGroup[p] = g;
            pDifficulty[p] = l;
        }
        else if (order[0] == 's') {
            int p;
            cin >> p;
            isSolved[p] = true;
            rQ[pGroup[p]].erase(rQ[pGroup[p]].find(Problem(p, pDifficulty[p])));
            rSet.erase(rSet.find(Problem(p, pDifficulty[p])));
        }
        else if (order.back() == 'd') {
            int g, x;
            cin >> g >> x;
            if (x == 1) cout << (--rQ[g].end())->id << endl;
            else cout << rQ[g].begin()->id << endl;
        }
        else if (order.back() == '2') {
            int x;
            cin >> x;
            if (x == 1) cout << (--rSet.end())->id << endl;
            else cout << rSet.begin()->id << endl;
        }
        else {
            int x, l;
            cin >> x >> l;
            auto pos = rSet.lower_bound(Problem(0, l));
            if (x == 1) cout << (pos == rSet.end() ? -1 : pos->id) << endl;
            else cout << (pos == rSet.begin() ? -1 : (--pos)->id) << endl;
        }
    }

    return 0;
}
