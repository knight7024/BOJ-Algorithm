import sys
sys.setrecursionlimit(10 ** 8)

def dfs(index, sum, depth):
	global ans
	if depth and index == n and sum == s:
		ans += 1
	
	if (index + 1 <= n):
		dfs(index + 1, sum, depth)
		dfs(index + 1, sum + arr[index], depth + 1)

n, s = map(int, input().split())
arr = list(map(int, input().split()))

ans = 0
dfs(0, 0, 0)

print(ans)
