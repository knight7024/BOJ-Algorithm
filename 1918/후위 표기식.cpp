#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Ops {
	int priority;
	int bracketCount;
	char oper;
	Ops(int priority, int bracketCount, char oper) : priority(priority), bracketCount(bracketCount), oper(oper) {}
};

int priority[48];

int main() {
	string s;
	cin >> s;

	priority['+'] = priority['-'] = 1;
	priority['*'] = priority['/'] = 2;

	stack<Ops> postfix;
	int bracket = 0;
	for (int i = 0; i < s.size(); i++) {
		char c = s[i];

		// 알파벳이면 그냥 출력
		if (isalpha(c)) cout << c;
		else {
			// 괄호라면
			if (c == '(') bracket++;
			else if (c == ')') {
				while (!postfix.empty() && postfix.top().bracketCount == bracket) {
					cout << postfix.top().oper;
					postfix.pop();
				}
				bracket--;
			}
			// 사칙연산자라면
			if (c == '*' || c == '/' || c == '+' || c == '-') {
				if (!postfix.empty() && postfix.top().priority >= priority[int(c)]) {
					while (!postfix.empty() && postfix.top().bracketCount == bracket && postfix.top().priority >= priority[int(c)]) {
						cout << postfix.top().oper;
						postfix.pop();
					}
				}
				postfix.emplace(priority[c], bracket, c);
			}
		}
	}

	while (!postfix.empty()) {
		cout << postfix.top().oper;
		postfix.pop();
	}

	return 0;
}
