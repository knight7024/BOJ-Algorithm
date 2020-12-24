#include <iostream>
#include <algorithm>

using namespace std;

int targetR, targetC;
int visit;

bool divideAndConquer(int nowR, int nowC, int nowLen)
{
	// 방문할 행열이 현재 방문할 수 있는 사분면보다 멀리 있는 곳에 있다면
	// 방문할 가치가 없는 사분면이다
	if (nowR + nowLen < targetR || nowC + nowLen < targetC) {
		visit += nowLen * nowLen;
		return false;
	}

    if (nowLen == 2)
    {
        if (nowR == targetR && nowC == targetC) return true;
        else if (nowR == targetR && nowC + 1 == targetC)
        {
            visit += 1;
            return true;
        }
        else if (nowR + 1 == targetR && nowC == targetC)
        {
            visit += 2;
            return true;
        }
        else if (nowR + 1 == targetR && nowC + 1 == targetC)
        {
            visit += 3;
            return true;
        }
        else visit += 4;
        return false;
    }
	
    bool result = divideAndConquer(nowR, nowC, nowLen / 2);
    if (result) return true;
    result = divideAndConquer(nowR, nowC + nowLen / 2, nowLen / 2);
    if (result) return true;
    result = divideAndConquer(nowR + nowLen / 2, nowC, nowLen / 2);
    if (result) return true;
    result = divideAndConquer(nowR + nowLen / 2, nowC + nowLen / 2, nowLen / 2);
	
    return result;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n >> targetR >> targetC;

    divideAndConquer(0, 0, 1 << n);
    cout << visit;

    return 0;
}
