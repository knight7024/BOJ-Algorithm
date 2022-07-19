n = int(input())
arr = list(map(int, input().split()))
prefixSum = [0]
for i in arr:
	prefixSum.append(prefixSum[-1] + i)

answer = 0
for i, _ in enumerate(arr):
	if 0 < i < len(arr) - 1:
		answer = max(answer, prefixSum[-1] + prefixSum[-1] - prefixSum[i] - arr[0] - 2 * arr[i])
		answer = max(answer, prefixSum[-1] + prefixSum[i + 1] - arr[-1] - 2 * arr[i])
		answer = max(answer, prefixSum[i + 1] - prefixSum[1] + prefixSum[-1] - prefixSum[i] - arr[-1])

print(answer)
