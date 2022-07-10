import sys
input = sys.stdin.readline

n, m = map(int, input().split())
meats = sorted([tuple(map(int, input().split())) for _ in range(n)], key=lambda a: (a[1], -a[0]))

answer = 1 << 31
wSum1, tSum = 0, 0
wSum2, vSum = 0, 0
for i, (w, v) in enumerate(meats):
	if i == 0:
		wSum1 += w
		wSum2 += w
		vSum += v
	elif i > 0 and meats[i - 1][1] != v:
		wSum1 += tSum + w
		tSum = 0
		wSum2 = wSum1
		vSum = v
	elif i > 0 and meats[i - 1][1] == v:
		wSum1 += w - meats[i - 1][0]
		tSum += meats[i - 1][0]
		wSum2 += w
		vSum += v
	if wSum1 >= m:
		answer = min(answer, v)
	if wSum2 >= m:
		answer = min(answer, vSum)

print(-1 if answer == 1 << 31 else answer)
