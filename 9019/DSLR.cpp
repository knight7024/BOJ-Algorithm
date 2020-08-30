#include <algorithm>
#include <iostream>
#include <queue>
#define MOD 10000
#define endl '\n'

using namespace std;

char type[] = {'D', 'S', 'L', 'R'};

struct Register {
	int num;
	unsigned long order;
};

int D(int num) {
	return (2 * num) % MOD;
}

int S(int num) {
	return (num - 1 + MOD) % MOD;
}

int L(int num) {
	return (num * 10) % 10000 + num / 1000;
}

int R(int num) {
	return (num % 10) * 1000 + num / 10;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	int a, b;
	while (t--) {
		cin >> a >> b;

		queue<Register> bfs;
		bool visited[10001]{};

		bfs.push({a, 0});
		visited[a] = true;

		while (!bfs.empty()) {
			auto front = bfs.front();
			bfs.pop();

			int num = front.num;
			if (num == b) {
				string temp = to_string(front.order);
				for (int i = 0; i < temp.size(); i++) {
					cout << type[temp[i] - '1'];
				}
				cout << endl;
				break;
			}

			if (!visited[D(num)]) {
				bfs.push({D(num), front.order * 10 + 1});
				visited[D(num)] = true;
			}
			if (!visited[S(num)]) {
				bfs.push({S(num), front.order * 10 + 2});
				visited[S(num)] = true;
			}
			if (!visited[L(num)]) {
				bfs.push({L(num), front.order * 10 + 3});
				visited[L(num)] = true;
			}
			if (!visited[R(num)]) {
				bfs.push({R(num), front.order * 10 + 4});
				visited[R(num)] = true;
			}
		}
	}
	return 0;
}
