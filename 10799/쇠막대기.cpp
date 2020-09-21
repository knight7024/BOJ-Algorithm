#include <iostream>
#include <string>

using namespace std;

int main() {
	string arrangement;
	cin >> arrangement;

    int leftCnt = 0;
    int partition = 0;
    for (int i = 0; i < arrangement.size(); i++) {
        // (가 발견됐는데
        if (arrangement[i] == '(') {
            // 바로 )가 나오면 레이저
            if (arrangement[i + 1] == ')') {
                partition += leftCnt;
                i++;
            }
            // 아니면 쇠막대기 개수 올려줌
            else {
                leftCnt++;
            }
        }
        // 쇠막대기 끝부분이면
        // 조각 개수 하나 올려주고 막대기 개수 줄임
        else if (arrangement[i] == ')') {
            partition += 1;
            leftCnt--;
        }
    }

	cout << partition;
	return 0;
}
