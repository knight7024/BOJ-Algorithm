#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

class GoStack {
private:
    const long MAX = 1e9;

    stack<long> stk;
    bool isError = false;

public:
    void num(long x) {
        stk.push(x);
        isError |= abs(stk.top()) > MAX;
    }

    void pop() {
        if (stk.empty()) {
            isError = true;
            return;
        } 
        stk.pop();
    }

    void inv() {
        if (stk.empty()) {
            isError = true;
            return;
        }
        long top = stk.top();
        stk.pop();
        stk.push(-top);
    }

    void dup() {
        if (stk.empty()) {
            isError = true;
            return;
        }
        stk.push(stk.top());
    }

    void swp() {
        if (stk.size() < 2) {
            isError = true;
            return;
        }
        long a = stk.top(); stk.pop();
        long b = stk.top(); stk.pop();
        stk.push(a); stk.push(b);
    }

    void add() {
        if (stk.size() < 2) {
            isError = true;
            return;
        }
        long a = stk.top(); stk.pop();
        long b = stk.top(); stk.pop();
        stk.push(b + a);
        isError |= abs(stk.top()) > MAX;
    }

    void sub() {
        if (stk.size() < 2) {
            isError = true;
            return;
        }
        long a = stk.top(); stk.pop();
        long b = stk.top(); stk.pop();
        stk.push(b - a);
        isError |= abs(stk.top()) > MAX;
    }

    void mul() {
        if (stk.size() < 2) {
            isError = true;
            return;
        }
        long a = stk.top(); stk.pop();
        long b = stk.top(); stk.pop();
        stk.push(b * a);
        isError |= abs(stk.top()) > MAX;
    }

    void div() {
        if (stk.size() < 2) {
            isError = true;
            return;
        }
        long a = stk.top(); stk.pop();
        long b = stk.top(); stk.pop();
        if (!a) {
            isError = true;
            return;
        }
        stk.push(b * a >= 0 ? abs(b) / abs(a) : -(abs(b) / abs(a)));
        isError |= abs(stk.top()) > MAX;
    }

    void mod() {
        if (stk.size() < 2) {
            isError = true;
            return;
        }
        long a = stk.top(); stk.pop();
        long b = stk.top(); stk.pop();
        if (!a) {
            isError = true;
            return;
        }
        stk.push(b - a * (b * a >= 0 ? abs(b) / abs(a) : -(abs(b) / abs(a))));
        isError |= abs(stk.top()) > MAX;
    }

    void clear() {
        stk = {};
        isError = false;
    }

    long getTop() {
        return stk.top();
    }

    int getSize() {
        return stk.size();
    }

    bool getError() {
        return isError;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    GoStack go;
    string op;
    vector<string> ops;
    while (1) {
        getline(cin, op);
        if (op == "QUIT") break;
        else if (isdigit(op[0])) {
            int n = stoi(op);
            while (n--) {
                int v;
                cin >> v;

                go.clear(); go.num(v);
                for (const auto& s : ops) {
                    if (go.getError()) break;
                    if (s[0] == 'N') {
                        long x = stol(s.substr(4));
                        go.num(x);
                    }
                    else if (s == "POP") go.pop();
                    else if (s == "INV") go.inv();
                    else if (s == "DUP") go.dup();
                    else if (s == "SWP") go.swp();
                    else if (s == "ADD") go.add();
                    else if (s == "SUB") go.sub();
                    else if (s == "MUL") go.mul();
                    else if (s == "DIV") go.div();
                    else if (s == "MOD") go.mod();
                    else if (s == "END") break;
                }

                if (go.getError() or go.getSize() != 1) cout << "ERROR" << endl;
                else cout << go.getTop() << endl;
            }
            cout << endl;
            cin.ignore(); ops.clear();
        }
        else ops.emplace_back(op);
    }
    
    return 0;
}
