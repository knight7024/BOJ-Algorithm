#include <iostream>
#include <map>
using namespace std;

struct Slope {
	long x, y;
	Slope() {}
	Slope(long x, long y) {
		if (x < 0) this->x = -x, this->y = -y;
		else this->x = x, this->y = y;
	}
	bool operator<(const Slope& a) const { return x == a.x ? y < a.y : x < a.x; }
};

long gcd(long a, long b) {
	return !a ? b : gcd(b % a, a);
}

long pairCount(long n) {
	return n * (n - 1) / 2;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	long n;
	cin >> n;

	map<Slope, long> slope;
	for (int i = 0; i < n; i++) {
		long a, b, c;
		cin >> a >> b >> c;
		long g = gcd(a, b);
		Slope temp = Slope(a / g, b / g);
		if (slope.find(temp) == slope.end()) slope.emplace(temp, 1);
		else slope[temp]++;
	}

	long allCount = pairCount(n);
	for (auto& it : slope) {
		if (it.second == 1) continue;
		allCount -= pairCount(it.second);
	}

	cout << allCount;

	return 0;
}
