#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

class DoubleSeedRollingHash {
private:
    const int SEED1 = 17;
    const int SEED2 = 31;
      const long MOD = (1L << 31) - 1;

    long maxPow1 = 1;
    long maxPow2 = 1;

    int startPos = 0;
    int endPos = 0;
    string targetStr;

    long hashValue1 = 0;
    long hashValue2 = 0;

public:
    DoubleSeedRollingHash(string& input, int size) {
        if (input.size() < size) throw out_of_range("");
        targetStr = input; endPos = size;
        for (int i = size - 1; i >= 0; i--) {
            hashValue1 = (hashValue1 + (maxPow1 * input[i]) & MOD) & MOD;
            if (i) maxPow1 = (maxPow1 * SEED1) & MOD;

            hashValue2 = (hashValue2 + (maxPow2 * input[i]) & MOD) & MOD;
            if (i) maxPow2 = (maxPow2 * SEED2) & MOD;
        }
    }

    DoubleSeedRollingHash(string& input, int start, int end) {
        if (start < 0 or start >= end or input.size() < end) throw out_of_range("");
        targetStr = input; startPos = start; endPos = end;
        for (int i = end - 1; i >= start; i--) {
            hashValue1 = (hashValue1 + (maxPow1 * input[i]) & MOD) & MOD;
            if (i > start) maxPow1 = (maxPow1 * SEED1) & MOD;

            hashValue2 = (hashValue2 + (maxPow2 * input[i]) & MOD) & MOD;
            if (i > start) maxPow2 = (maxPow2 * SEED2) & MOD;
        }
    }

    bool operator==(const DoubleSeedRollingHash& a) const {
        return hashValue1 == a.hashValue1 and hashValue2 == a.hashValue2;
    }

    bool operator==(const pair<long, long>& a) const {
        return hashValue1 == a.first and hashValue2 == a.second;
    }

    bool operator!=(const DoubleSeedRollingHash& a) const {
        return !(*this == a);
    }

    bool operator!=(const pair<long, long>& a) const {
        return !(*this == a);
    }

    void roll() {
        if (targetStr.size() < endPos) throw out_of_range("");
        hashValue1 = ((((hashValue1 - (targetStr[startPos] * maxPow1) & MOD) * SEED1) & MOD) + targetStr[endPos]) & MOD;
        hashValue2 = ((((hashValue2 - (targetStr[startPos] * maxPow2) & MOD) * SEED2) & MOD) + targetStr[endPos]) & MOD;
        startPos++; endPos++;
    }

    pair<long, long> getHash() {
        return {hashValue1, hashValue2};
    }
};

class DoubleSeedHash {
private:
    const int SEED1 = 4;
    const int SEED2 = 5;
      const long MOD = (1L << 31) - 1;

    long hashValue1 = 0;
    long hashValue2 = 0;

public:
    DoubleSeedHash(string& input, int size) {
        if (input.size() < size) throw out_of_range("");
        for (int i = 0; i < size; i++) {
            hashValue1 = ((((hashValue1 << SEED1) + hashValue1) & MOD) + input[i]) & MOD;
            hashValue2 = ((((hashValue2 << SEED2) - hashValue2) & MOD) + input[i]) & MOD;
        }
    }

    DoubleSeedHash(string& input, int start, int end) {
        if (start < 0 or start >= end or input.size() < end) throw out_of_range("");
        for (int i = start; i < end; i++) {
            hashValue1 = ((((hashValue1 << SEED1) + hashValue1) & MOD) + input[i]) & MOD;
            hashValue2 = ((((hashValue2 << SEED2) - hashValue2) & MOD) + input[i]) & MOD;
        }
    }

    DoubleSeedHash& operator=(const DoubleSeedHash& a) {
        hashValue1 = a.hashValue1;
        hashValue2 = a.hashValue2;
        return *this;
    }

    bool operator==(const DoubleSeedHash& a) const {
        return hashValue1 == a.hashValue1 and hashValue2 == a.hashValue2;
    }

    bool operator==(const pair<long, long>& a) const {
        return hashValue1 == a.first and hashValue2 == a.second;
    }

    bool operator!=(const DoubleSeedHash& a) const {
        return !(*this == a);
    }

    bool operator!=(const pair<long, long>& a) const {
        return !(*this == a);
    }

    pair<long, long> getHash() {
        return {hashValue1, hashValue2};
    }
};

struct pairHash {
    template <class T1, class T2>
    size_t operator() (const pair<T1, T2>& a) const {
        return hash<T1>()(a.first) ^ hash<T2>()(a.second);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        string a, w, s;
        cin >> a >> w >> s;

        unordered_map<char, char> shift;
        for (int i = 0; a[i]; i++) {
            shift[a[i]] = a[(i + 1) % a.size()];
        }

        unordered_map<pair<long, long>, int, pairHash> hashes;
        DoubleSeedHash seedHash(w, w.size());
        hashes[seedHash.getHash()] = 0;
        
        for (int i = 1; a[i]; i++) {
            for (int j = 0; w[j]; j++) {
                w[j] = shift[w[j]];
            }
            seedHash = DoubleSeedHash(w, w.size());
            hashes[seedHash.getHash()] = i;
        }

        int shiftCnt[63] {};
        DoubleSeedRollingHash rollingHash(s, w.size());
        if (hashes.count(rollingHash.getHash())) shiftCnt[hashes[rollingHash.getHash()]]++;
        for (int i = 1; i <= s.size() - w.size(); i++) {
            rollingHash.roll();
            if (hashes.count(rollingHash.getHash())) shiftCnt[hashes[rollingHash.getHash()]]++;
        }

        vector<int> shiftValues;
        for (int i = 0; i < a[i]; i++) {
            if (shiftCnt[i] != 1) continue;
            shiftValues.push_back(i);
        }

        if (shiftValues.empty()) cout << "no solution" << endl;
        else if (shiftValues.size() == 1) cout << "unique: " << shiftValues[0] << endl;
        else {
            cout << "ambiguous: ";
            for (int i : shiftValues) cout << i << ' ';
            cout << endl;
        }
    }
    
    return 0;
}
