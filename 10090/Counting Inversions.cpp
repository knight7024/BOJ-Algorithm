#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int arr[1000001];
int sorted[1000001];
long answer;

void mergeSort(int from, int mid, int to) {
    int sIdx = 0;
    int leftStart = from, rightStart = mid + 1;
    int size = to - from;
    while (leftStart <= mid and rightStart <= to) {
        if (arr[leftStart] < arr[rightStart]) {
            answer += to - leftStart > size - sIdx ? to - leftStart - (size - sIdx) : 0;
            sorted[sIdx++] = arr[leftStart++];
        }
        else {
            answer += to - rightStart > size - sIdx ? to - rightStart - (size - sIdx) : 0;
            sorted[sIdx++] = arr[rightStart++];
        }
    }

    while (leftStart <= mid) {
        answer += to - leftStart > size - sIdx ? to - leftStart - (size - sIdx) : 0;
        sorted[sIdx++] = arr[leftStart++];
    }

    while (rightStart <= to) {
        answer += to - rightStart > size - sIdx ? to - rightStart - (size - sIdx) : 0;
        sorted[sIdx++] = arr[rightStart++];
    }

    for (int i = from; i <= to; i++) arr[i] = sorted[i - from];
}

void divide(int from, int to) {
    if (from == to) return;

    int mid = (from + to) / 2;
    divide(from, mid);
    divide(mid + 1, to);

    mergeSort(from, mid, to);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    divide(0, n - 1);

    cout << answer;

    return 0;
}
