#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#define endl '\n'
using namespace std;

int main() {
	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		queue<pair<string, int>> q;
		bool visited[20001] {};
		q.emplace("1", 1);
		visited[1] = true;

		while (!q.empty()) {
			auto front = q.front();
			q.pop();

			if (front.second % n == 0) {
				cout << front.first << endl;
				break;
			}

			string str1 = front.first + "0";
			int num1 = front.second * 10;
			if (!visited[num1 % n]) {
				visited[num1 % n] = true;
				q.emplace(front.first + "0", num1 % n);
			}

			int num2 = front.second * 10 + 1;
			if (!visited[num2 % n]) {
				visited[num2 % n] = true;
				q.emplace(front.first + "1", num2 % n);
			}
		}
	}
}
