#include <iostream>
#include <vector>
#define INF 987654321
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	vector<int> elec(k + 1);
	for (int i = 1; i <= k; i++) {
		cin >> elec[i];
	}

	bool check[101] {};
	int checkCount = 0;
	int count = 0;
	for (int i = 1; i <= k; i++) {
		int e = elec[i];
		// 이미 꽂은 전기용품이면 넘어간다.
		if (check[e]) continue;

		// 멀티탭 구멍의 개수만큼 전기 용품을 덜 꽂은 경우
		if (checkCount < n) {
			check[e] = true;
			++checkCount;
			continue;
		}
		
		// 멀티탭 구멍이 부족한 경우
		int maxDist = -1;
		int maxElec = -1;
		for (int j = 1; j <= k; j++) {
			// 현재 사용 중인 것 중에서 가장 멀리 있는 전기 용품 찾는다.
			if (!check[j]) continue;

			int dist = INF;
			for (int m = i + 1; m <= k; m++) {
				if (elec[m] != j) continue;
				dist = m - i;
				break;
			}

			if (maxDist < dist) {
				maxDist = dist;
				maxElec = j;
			}
		}

		if (maxDist != -1) {
			check[maxElec] = !(check[e] = true);
			count++;
		}
	}

	cout << count;
	return 0;
}
