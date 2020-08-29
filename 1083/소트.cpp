#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;
	
	vector<int> arr(N + 1);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	
	int S;
	cin >> S;
	
	for (int i = 0; i < N; i++) {
		int swapIdx = i;
		for (int j = i + 1; j < N && j <= i + S; j++) {
			if (arr[swapIdx] < arr[j]) {
				swapIdx = j;
			}
		}
		
		int temp = arr[swapIdx];
		arr.erase(arr.begin() + swapIdx);
		arr.insert(arr.begin() + i, temp);
		S -= swapIdx - i;
	}
	
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	return 0;
}
