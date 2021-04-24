#include <iostream>
#include <vector>
using namespace std;

struct Coor {
	long x, y;
};

struct Math {
	// 계수, 상수
	long coeff, cons;
};

// 목적: [i,i+1]의 함수가 kx와 만나는 점이 있는지
// 1. ax+b=cx => x=b/(c-a)
// 2. x가 [i,i+1]에 있는가 여부 판단
bool isMeet(int i, Math a, Math b) {
	if (a.coeff == b.coeff) return a.cons == 0;
	double x = (double) a.cons / (b.coeff - a.coeff);
	return x && x >= i && x <= i + 1;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<Coor> func;
	func.push_back({0, 0});
	for (int i = 1; i <= n; i++) {
		long y;
		cin >> y;
		func.push_back({i, y});
	}

	long k;
	cin >> k;

	// [i,i+1]의 함수 방정식은 (coeff)x + (cons)
	vector<Math> eq;
	for (int i = 0; i < n; i++) {
		long coeff = func[i + 1].y - func[i].y;
		long cons = func[i].y - (coeff * func[i].x);
		eq.push_back({coeff, cons});
	}

	for (int i = 0; i < n; i++) {
		if (isMeet(i, eq[i], {k, 0})) {
			cout << 'T';
			exit(0);
		}
	}

	cout << 'F';

	return 0;
}
