#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

struct Node {
    string name;
    map<string, Node*> dic;
    Node() {}
    Node(string name): name(name) {}
};

void dfs(map<string, Node*>* root, int depth) {
    for (auto& k : *root) {
        cout << string(depth * 2, '-') << k.first << endl;
        dfs(&k.second->dic, depth + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    map<string, Node*> root;
    string s;
    while (n--) {
        int k;
        cin >> k;

        map<string, Node*>* nowNode = &root;
        for (int i = 0; i < k; i++) {
            cin >> s;
            if (nowNode->count(s)) nowNode = &(*nowNode)[s]->dic;
            else {
                Node* newNode = new Node(s);
                (*nowNode)[s] = newNode;
                nowNode = &newNode->dic;
            }
        }
    }

    dfs(&root, 0);
    
    return 0;
}
