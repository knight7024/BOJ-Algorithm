from math import ceil
import sys
input = sys.stdin.readline

n, l = map(int, input().split())
arr = sorted([list(map(int, input().split())) for _ in range(n)])
end = -1
answer = 0
for a, b in arr:
	if b <= end: continue
	start = max(a, end + 1)
	cnt = ceil((b - start) / l)
	answer += cnt
	end = start + l * cnt - 1;
print(answer)
