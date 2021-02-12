import math
n, k = map(int, input().split())
coins = set()
for i in range(n):
	coins.add(int(input()))
dp = [math.inf for _ in  range(100001)]
dp[0] = 0
for j in range(1, k + 1):
	for i in coins:
		if i > j: continue
		dp[j] = min(dp[j], dp[j - i] + 1)
print(dp[k] if dp[k] != math.inf else -1)
