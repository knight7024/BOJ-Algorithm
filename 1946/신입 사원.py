import sys
input = sys.stdin.readline
print = sys.stdout.write
t = int(input())
while t:
	n = int(input())
	score = sorted([tuple(map(int, input().split())) for _ in range(n)])
	answer, minB = 0, n + 1
	for a, b in score:
		if minB > b:
			minB = b
			answer += 1
	print(f'{answer} ')
	t -= 1
