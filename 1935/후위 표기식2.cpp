#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

stack<double> nums;
queue<char> ops;

void calculate() {
	// 알파벳 먼저 빼고
	double num = nums.top();
	nums.pop();

	while (!ops.empty()) {
		double num2 = nums.top();
		// 연산자 빼고
		char op = ops.front();
        switch (op) {
        case '+':
			num = num2 + num;
            break;

        case '-':
			num = num2 - num;
            break;

        case '*':
			num = num2 * num;
            break;

        case '/':
			num = num2 / num;
            break;
        }
		ops.pop();
		nums.pop();
	}

	nums.push(num);
}

int main() {
	int n;
	cin >> n;

	string s;
	cin >> s;

	int matching[26];
	for (int i = 0; i < n; i++) {
		cin >> matching[i];
	}

	for (char c : s) {
		if (isalpha(c)) {
			if (!ops.empty()) calculate();
			nums.push(matching[c - 'A']);
		}
		else ops.push(c);
	}

	if (!ops.empty()) calculate();

	cout.precision(2);
	cout << fixed << nums.top();

	return 0;
}
