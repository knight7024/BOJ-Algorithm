#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define endl '\n'
#define MOD 1000000007
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
vector<int> obj;
vector<vector<int>> divisors;
int dp[301][2001];

int recur(int objIdx, int divIdx) {
	if (objIdx == n - 1) return 1;
	int& ret = dp[objIdx][divIdx];
	if (ret != INF) return ret;

	int result = 0;
	for (int i = 0; i < divisors[objIdx + 1].size(); i++) {
		if (divisors[objIdx][divIdx] > divisors[objIdx + 1][i]) continue;
		result = (result % MOD + recur(objIdx + 1, i) % MOD) % MOD;
	}

	return ret = result;
}

// 약수 구하기
void getDivisor(int idx) {
	if (idx > n) return;

	int nowObj = obj[idx];
	for (int i = 1; i * i <= nowObj; i++) {
		if (nowObj % i == 0) {
			divisors[idx].push_back(i);
			if (i != nowObj / i) {
				divisors[idx].push_back(nowObj / i);
			}
		}
	}

	getDivisor(idx + 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;

	while (t--) {
		cin >> n;

		obj.resize(n); obj.clear();
		for (int i = 0; i < n; i++) {
			cin >> obj[i];
		}

		divisors.resize(n); divisors.clear();
		getDivisor(0);

		memset(dp, INF, sizeof(dp));

		int answer = 0;
		for (int i = 0; i < divisors[0].size(); i++) {
			answer = (answer % MOD + recur(0, i) % MOD) % MOD;
		}

		cout << answer << endl;
	}

	return 0;
}
