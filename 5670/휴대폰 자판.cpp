#include <algorithm>
#include <cstring>
#include <iostream>
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
			int curr = *key - 'a';
			if (!next[curr]) next[curr] = new Trie();
			next[curr]->insert(key + 1);
		}
	}
	int find(const char *key, int depth) {
		// Base Case #1: 문자열을 끝까지 검색했는데 없을 경우
		if (!*key) return depth;

		int curr = *key - 'a';
		// 다음으로 이어질 단어가 하나 밖에 없고,
		// 현재 상태에서 끝나는 단어가 없다면 자동으로 입력해 준다.
		if (depth && this->count() == 1 && !isFinished) {
			return next[curr]->find(key + 1, depth);
		}

		// 아니라면 사용자의 입력을 기다려야 한다.
		return next[curr]->find(key + 1, depth + 1);
	}
	int count() {
		int found = 0;
		for (int i = 0; i < LEN; i++) {
			found += next[i] != NULL;
		}
		return found;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.setf(ios::fixed);
	cout.precision(2);

	int n;
	while (cin >> n) {
		vector<string> dic;
		Trie *trie = new Trie();

		for (int i = 0; i < n; i++) {
			string word;
			cin >> word;

			dic.push_back(word);
			trie->insert(word.c_str());
		}

		double ans = 0;
		for (auto &word : dic) {
			ans += trie->find(word.c_str(), 0);
		}

		cout << ans / n << endl;
		delete (trie);
	}
}
