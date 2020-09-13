def gcd(a, b):
	if b == 0: return a
	return gcd(b, a % b)

t = int(input())
for _ in range(t):
	inputList = list(map(int, input().split()))
	ans = 0
	for a in range(1, len(inputList) - 1):
		for b in range(a + 1, len(inputList)):
			ans += gcd(inputList[a], inputList[b])
	print(ans)
