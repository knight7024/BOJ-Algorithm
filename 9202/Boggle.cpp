#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#define LEN 26
#define endl '\n'
using namespace std;

struct Trie {
	bool isFinished;
	Trie *next[LEN];
	Trie() : isFinished(false) {
		memset(next, 0, sizeof(next));
	}
	~Trie() {
		for (int i = 0; i < LEN; i++) {
			if (next[i]) delete (next[i]);
		}
	}
	void insert(const char *key) {
		if (!*key) isFinished = true;
		else {
			int curr = *key - 'A';
			if (!next[curr]) next[curr] = new Trie();
			next[curr]->insert(key + 1);
		}
	}
	int find(const char *key) {
		if (!*key && isFinished) return 2;
		if (!*key) return 1;

		int curr = *key - 'A';
		if (!next[curr]) return 0;

		return next[curr]->find(key + 1);
	}
	int count() {
		int found = 0;
		for (int i = 0; i < LEN; i++) {
			found += next[i] != NULL;
		}
		return found;
	}
};

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
Trie *root = nullptr;
bool visited[4][4];
string findWord;
set<string> boggle;
int score[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};

void dfs(char board[5][5], int y, int x) {
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4) {
			if (visited[ny][nx]) continue;

			findWord.push_back(board[ny][nx]);
			int resultType = root->find(findWord.c_str());
			if (resultType) {
				if (resultType == 2) boggle.insert(findWord);
				visited[ny][nx] = true;
				dfs(board, ny, nx);
				visited[ny][nx] = false;
			}
			findWord.pop_back();
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	root = new Trie();
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		root->insert(s.c_str());
	}

	int t;
	cin >> t;

	while (t--) {
		char board[5][5];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> board[i][j];
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				findWord.push_back(board[i][j]);
				visited[i][j] = true;
				dfs(board, i, j);
				visited[i][j] = false;
				findWord.pop_back();
			}
		}

		int sum = 0;
		int maxLen = -1;
		auto maxIt = boggle.cbegin();
		for (auto i = boggle.cbegin(); i != boggle.cend(); i++) {
			int len = (*i).length();
			sum += score[len];
			if (len > maxLen) {
				maxLen = len;
				maxIt = i;
			}
		}

		cout << sum << ' ' << *maxIt << ' ' << boggle.size() << endl;
		boggle.clear();
	}
}
