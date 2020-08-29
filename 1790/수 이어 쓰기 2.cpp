#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long pow(long a, long b) {
    if (!b) return 1;
    long result = a;
    while (--b) result *= a;
    return result;
}

int main() {
    long N, k;
    cin >> N >> k;
    // 10번째 자리 미만이면 그냥 출력
    if (k < 10) {
        cout << k;
        return 0;
    }

    // 초기 작업: 자릿수 별로 개수 채워넣기
    // 9개, 90개, 900개, 9000개...
    // 1-9, 10-99, 100-999, 1000-9999...
    long num[11];
    // 10자리수는 1000000000 하나이다.
    num[10] = 1;
    for (int i = 1; i < 10; i++) {
        long from = pow(10, i - 1);
        long to = pow(10, i);
        num[i] = (to - from) * i;
    }

    long prefix = num[1];
    for (int i = 2; i < N; i++) {
        // 더한 게 더 크거나 같으면 현재 범위에 포함됨
        if (prefix + num[i] >= k) {
            // 만약 19번째 수를 구하고 싶다면,
            // 19 - num[1] - 1 = 9을 현재 자릿수 2로 나눈다.
            // pow(10, 2) + (9 / 2) = 14
            // 나머지가 1이니 4 출력
            long order = k - prefix - 1;
            long original = pow(10, i - 1) + (order / i);
            if (original > N) cout << -1;
            else cout << to_string(original)[order % i];
            break;
        }
        // 아니면 더해주고 넘어간다.
        prefix += num[i];
    }
    return 0;
}
