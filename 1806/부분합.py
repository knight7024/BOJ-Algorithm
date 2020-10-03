# 부분합 + 이분탐색 풀이
# O(NlogN)
n, s = map(int, input().split())
arr = [0]
arr.extend(list(map(int, input().split())))

for i in range(n):
	arr[i + 1] += arr[i]

minRange = 987654321
for i in range(0, n):
	start, end, lastEnd = i, n, n
	while start < end:
		mid = (start + end) // 2
		ret = arr[end] - arr[i]
		if ret < s:
			start, end = end, lastEnd
		else:
			minRange = min(minRange, end - i)
			lastEnd, end = end, mid
	
	
print(0 if minRange == 987654321 else minRange)
