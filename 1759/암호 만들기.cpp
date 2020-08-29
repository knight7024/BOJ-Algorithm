#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define endl '\n'

using namespace std;

char comb[16];
char vowels[] = "aeiou";
bool visited[16];
int L, C;

void backtracking(int start, int last, int vow, int cons) {
	if (!last) {
		if (vow < 1 || cons < 2) return;
		for (int i = 0; i < C; i++) {
			if (visited[i]) cout << comb[i];
		}
		cout << endl;
		return;
	}

	for (int i = start; i < C; i++) {
		// 현재 단어가 모음이면
		if (strchr(vowels, comb[i])) {
			visited[i] = true;
			backtracking(i + 1, last - 1, vow + 1, cons);
			visited[i] = false;
		}
		// 자음이면
		else {
			visited[i] = true;
			backtracking(i + 1, last - 1, vow, cons + 1);
			visited[i] = false;
		}
	}
}


int main() {
	cin.tie(0); cout.tie(0);
	ios_base::sync_with_stdio(0);

	cin >> L >> C;

	for (int i = 0; i < C; i++) cin >> comb[i];
	// 문자들 오름차순으로 정렬
	sort(comb, comb + C);

	backtracking(0, L, 0, 0);
	return 0;
}
