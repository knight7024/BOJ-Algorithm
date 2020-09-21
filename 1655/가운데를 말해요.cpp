#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define endl '\n'

using namespace std;

int main() {
    int N;
    cin >> N;

    // 좌측에서는 큰 수부터 꺼내야하고,
    priority_queue<int> left;
    // 우측에서는 작은 수부터 꺼내야한다.
    priority_queue<int, vector<int>, greater<int>> right;
    
    // 먼저 2개를 받자.
    int num;
    cin >> num;
    cout << num << endl;
    // 그런데 총 개수가 2개가 안되면 종료한다.
    if (N < 2) return 0;
    int num2;
    cin >> num2;
    // 항상 작은 수를 먼저 말해야 하므로,
    int mid = min(num, num2);
    cout << mid << endl;
    right.push(max(num, num2));

    // 균형잡힌 트리의 형태로 생각하면 편하다. 대신 힙이 그걸 도와준다.
    // 항상 N / 2 개씩 가지고 있도록 나눠서 넣는다.
    for (int i = 2; i < N; i++) {
        cin >> num;
        // 다음 숫자가 중간값보다 크거나 같으면,
        if (mid <= num) {
            right.push(num);
        }
        // 다음 숫자가 중간값보다 작으면,
        else if (mid > num) {
            left.push(num);
            // 항상 작은 수를 먼저 말해야 하므로 작은 수의 개수가 더 많다면,
            if (left.size() > right.size()) {
                // 중간값을 좌측에서 가장 큰 수로 교체한다.
                right.push(mid);
                mid = left.top();
                left.pop();
            }
        }
        // 각각 N / 2개씩 균형잡히지 않으면
        if (right.size() > left.size() + 1) {
            left.push(mid);
            mid = right.top();
            right.pop();
        }
        else if (left.size() > right.size() + 1) {
            right.push(mid);
            mid = left.top();
            left.pop();
        }
        cout << mid << endl;
    }
}
