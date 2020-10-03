# 투 포인터 풀이
# O(N)

n, m = map(int, input().split())
arr = list(map(int, input().split()))

ans = 0
front = 0
end = 0
sum = arr[0]
while front < n and end < n:
	if sum == m:
		ans += 1
		end += 1
		if end < n:
			sum += arr[end]
	elif sum > m:
		if front == end:
			end += 1
			if end < n:
				sum += arr[end]
			continue
		sum -= arr[front]
		front += 1
	elif sum < m:
		end += 1
		if end < n:
			sum += arr[end]

print(ans)

'''
# 부분합 + 이분탐색 풀이
# O(NlogN)

n, m = map(int, input().split())
arr = [0]
arr.extend(list(map(int, input().split())))

for i in range(n):
	arr[i + 1] += arr[i]

ans = 0
for i in range(0, n):
	start = i
	end = n
	while start <= end:
		mid = (start + end) // 2
		ret = arr[mid] - arr[i]
		if ret == m:
			ans += 1
			break
		elif ret < m:
			start = mid + 1
		else:
			end = mid - 1

print(ans)
'''
