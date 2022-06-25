#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const long HASH_SIZE = (1L << 31) - 1;

long getHash(string& s, long p) {
    long hash = 0, powNum = 1;
    for (int i = s.size() - 1; i >= 0; i--) {
        hash = (hash + (powNum * s[i]) & HASH_SIZE) & HASH_SIZE;
        powNum = (powNum * p) & HASH_SIZE;
    }
    return hash;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int c, n;
    cin >> c >> n;

    string s;
    unordered_multimap<long, long> colorHash;
    for (int i = 0; i < c; i++) {
        cin >> s;
        colorHash.emplace(getHash(s, 31), getHash(s, 17));
    }

    unordered_multimap<long, long> nicknameHash;
    for (int i = 0; i < n; i++) {
        cin >> s;
        nicknameHash.emplace(getHash(s, 31), getHash(s, 17));
    }

    int q;
    cin >> q;

    while (q--) {
        cin >> s;

        pair<long, long> maxPow {1, 1};
        pair<long, long> powIndex[2000];
        for (int i = 0; s[i]; i++) {
            powIndex[i] = maxPow;
            maxPow.first = (maxPow.first * 31) & HASH_SIZE;
            maxPow.second = (maxPow.second * 17) & HASH_SIZE;
        }

        bool canWin = false;
        long colorHash1 = 0, colorHash2 = 0;
        long nicknameHash1 = getHash(s, 31), nicknameHash2 = getHash(s, 17);
        for (int i = 0; i < s.size() - 1; i++) {
            colorHash1 = ((((colorHash1 << 5) - colorHash1) & HASH_SIZE) + s[i]) & HASH_SIZE;
            colorHash2 = ((((colorHash2 << 4) + colorHash2) & HASH_SIZE) + s[i]) & HASH_SIZE;
            
            nicknameHash1 = (nicknameHash1 - (powIndex[s.size() - i - 1].first * s[i]) & HASH_SIZE) & HASH_SIZE;
            nicknameHash2 = (nicknameHash2 - (powIndex[s.size() - i - 1].second * s[i]) & HASH_SIZE) & HASH_SIZE;
            
            auto range1 = colorHash.equal_range(colorHash1);
            bool isOk1 = false;
            for (auto it = range1.first; it != range1.second; ++it) {
                if (it->second == colorHash2) {
                    isOk1 = true;
                    break;
                }
            }
            if (!isOk1) continue;
            
            auto range2 = nicknameHash.equal_range(nicknameHash1);
            for (auto it = range2.first; it != range2.second; ++it) {
                if (it->second == nicknameHash2) {
                    canWin = true;
                    break;
                }
            }
            if (canWin) break;
        }

        cout << (canWin ? "Yes" : "No") << endl;
    }
    
    return 0;
}
