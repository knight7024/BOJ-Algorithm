def dfs(n, g, v, s):
	v[s] = 1
	if not v[g[s - 1]]:
		return dfs(n, g, v, g[s - 1])
	return 1


t = int(input())
while t > 0:
	n = int(input())
	g = list(map(int, input().split()))
	v = [0 for i in range(n + 1)]
	a = 0
	for i in g:
		if v[i]: continue
		a += dfs(n, g, v, i)
	print(a)
	t -= 1
