#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> adj(81);
int maxSize;
string maxStr;

bool isOk(string& a, string& b) {
    int diff = 0;
    int i = 0, j = 0;
    while (i < a.size() and j < b.size()) {
        if (a[i] != b[j]) {
            diff++; j++;
            continue;
        }
        i++; j++;
    }
    return diff <= 1;
}

void dfs(string& s) {
    int size = s.size();
    if (maxSize < size) {
        maxSize = size;
        maxStr = s;
    }
    for (auto& i : adj[size + 1]) {
        if (!isOk(s, i)) continue;
        dfs(i);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int d; string word;
    cin >> d >> word;

    string s;
    for (int i = 0; i < d; i++) {
        cin >> s;
        adj[s.size()].push_back(s);
    }

    dfs(word);

    cout << maxStr;
    
    return 0;
}
