def backtracking(start, plus, minus, mult, div, result):
	global formula, maxResult, minResult

	if start == n - 1:
		maxResult = max(maxResult, result)
		minResult = min(minResult, result)
		return

	if plus:
		backtracking(start + 1, plus - 1, minus, mult, div, result + a[start + 1])

	if minus:
		backtracking(start + 1, plus, minus - 1, mult, div, result - a[start + 1])

	if mult:
		backtracking(start + 1, plus, minus, mult - 1, div, result * a[start + 1])

	if div:
		backtracking(start + 1, plus, minus, mult, div - 1, int(result / a[start + 1]))


n = int(input())
a = list(map(int, input().split()))
plus, minus, mult, div = map(int, input().split())

maxResult = -2147483648
minResult = 2147483647

backtracking(0, plus, minus, mult, div, a[0])

print(maxResult, minResult)
