#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, d, k, c;
	cin >> n >> d >> k >> c;

	vector<int> sushi(n * 2);
	for (int i = 0; i < n; i++) {
		cin >> sushi[i];
	}

	for (int i = n; i < n * 2; i++) {
		sushi[i] = sushi[i - n];
	}

	int from = 0, to = k - 1;
	int type = 0;
	int check[3001] {};
	for (int i = from; i <= to; i++) {
		type += check[sushi[i]]++ == 0;
	}

	int answer = 0;
	while (to < n * 2) {
		answer = max(answer, type + (check[c] == 0));
		type -= --check[sushi[from]] == 0;
		from++; to++;
		type += check[sushi[to]]++ == 0;
	}

	cout << answer;

	return 0;
}
