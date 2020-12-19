#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

bool graph[26][26];
int indegree[26];

int main() {
	int n;
	cin >> n;

	vector<string> algospot(n);
	bool check[26] {};
	int count = 0;
	for (int i = 0; i < n; i++) {
		cin >> algospot[i];
		for (char c : algospot[i]) {
			if (check[c - 'a']) continue;
			check[c - 'a'] = true;
			count++;
		}
	}

	// 모든 단어들에 대해 연관성을 검사
	for (int i = 0; i < n - 1; i++) {
		string& a = algospot[i];
		for (int j = i + 1; j < n; j++) {
			string& b = algospot[j];
			auto it1 = a.begin(), it2 = b.begin();
			bool isRelated = false;
			// 한 글자씩 탐색
			while (it1 != a.end() && it2 != b.end()) {
				int aWordIdx = *it1 - 'a', bWordIdx = *it2 - 'a';
				// 서로 일치하지 않는 부분이 나오면 연관성 만들어준다.
				if (aWordIdx != bWordIdx) {
					if (!graph[aWordIdx][bWordIdx]) indegree[bWordIdx]++;
					graph[aWordIdx][bWordIdx] = true;
					isRelated = true;
					break;
				}
				it1++; it2++;
			}
			
			if (isRelated) continue;
			// 서로 연관성 있는 단어인데 앞의 단어의 길이가 더 클 경우
			// 잘못된 순서이다.
			if (a.size() > b.size()) {
				cout << "!";
				exit(0);
			}
		}
	}

	// BFS 위상정렬
	// 들어오는 간선의 개수가 0인 정점들에서부터 BFS
	queue<int> topo;
	for (int i = 0; i < 26; i++) {
		if (!indegree[i] && check[i]) {
			topo.emplace(i);
		}
	}

	vector<char> result;
	while (!topo.empty()) {
        // 연결된 간선이 많다 == 가능한 순서가 여러 가지이다.
		if (topo.size() > 1) {
			cout << "?";
			exit(0);
		}
		int front = topo.front();
		result.push_back(front + 'a');
		topo.pop();

		for (int i = 0; i < 26; i++) {
			if (graph[front][i]) {
				if (!--indegree[i]) {
					topo.emplace(i);
				}
			}
		}
	}

	if (result.size() == count) {
		for (char c : result) cout << c;
	}
	else {
		cout << "!";
	}

	return 0;
}
