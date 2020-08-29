#include <algorithm>
#include <iostream>

using namespace std;

long line[200001];

struct Coor {
	int y;
	int x;
};

long getValue(Coor now) {
	long sum = now.y + now.x;
	long apb = line[sum];
	long amb = now.y - now.x;

	long one = (apb + amb) / 2;
	long another = (apb - amb) / 2;
	
	long minAns = min(one, another);
	long maxAns = max(one, another);
	
	return sum % 2 ? now.y <= now.x ? minAns : maxAns : now.y <= now.x ? maxAns : minAns;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int N, M;
	cin >> N >> M;

	int d = 1;
	line[1] = 1;
	for (int i = 2; i <= N + 1; i++) {
		line[i] = line[i - 1] + d;
		d += 2;
	}

	for (int i = N + 2; i <= 2 * N; i++) {
		d -= 2;
		line[i] = line[i - 1] + d;
	}

	Coor now{1, 1};
	long answer = 1;
	char order;
	for (int i = 0; i < M; i++) {
		cin >> order;

		switch (order) {
		case 'U':
			now.y -= 1;
			break;

		case 'D':
			now.y += 1;
			break;

		case 'R':
			now.x += 1;
			break;

		case 'L':
			now.x -= 1;
			break;
		}
		
		answer += getValue(now);
	}

	cout << answer;
	return 0;
}
