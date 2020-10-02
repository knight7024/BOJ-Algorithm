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
