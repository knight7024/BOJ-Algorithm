n, k = map(int, input().split())
coins = []
for i in range(n):
	coins.append(int(input()))
dp = [0 for _ in  range(100001)]
dp[0] = 1
for i in coins:
	for j in range(k + 1):
		dp[j] += dp[j - i]
print(dp[k])
