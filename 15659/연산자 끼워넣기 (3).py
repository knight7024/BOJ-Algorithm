def calc(eq):
	stack = []
	i = 0
	while i < len(eq):
		now = eq[i]
		if now in '*/':
			calcResult = int(eval('%s%c%s' % (stack[-1], now, eq[i + 1])))
			stack.pop()
			stack.append(str(calcResult))
			i += 1
		else: stack.append(now)
		i += 1
	return int(eval(''.join(stack)))

def backtracking(idx):
	global eq, opsCnt, maxResult, minResult
	eq.append(a[idx])
	if idx >= n - 1:
		result = calc(eq)
		maxResult = max(maxResult, result)
		minResult = min(minResult, result)
		eq.pop()
		return
	for i in range(4):
		if not opsCnt[i]: continue
		opsCnt[i] -= 1
		eq.append(ops[i])
		backtracking(idx + 1)
		eq.pop()
		opsCnt[i] += 1
	eq.pop()

n = int(input())
a = input().split()
opsCnt = list(map(int, input().split()))
ops = ['+', '-', '*', '/']
eq = []
maxResult = -(1 << 30)
minResult = 1 << 30
backtracking(0)
print(maxResult, minResult)
