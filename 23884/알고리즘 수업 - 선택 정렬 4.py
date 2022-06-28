n, k = map(int, input().split())
arr = list(map(int, input().split()))
sorted_arr = sorted(arr)
dic = {v: i for i, v in enumerate(arr)}
for i in range(n - 1, -1, -1):
	if not k: break
	if dic[sorted_arr[i]] == i: continue
	prevPos, nextPos = dic[sorted_arr[i]], i
	dic[arr[prevPos]], dic[arr[nextPos]] = nextPos, prevPos
	arr[prevPos], arr[nextPos] = arr[nextPos], arr[prevPos]
	k -= 1
if k: print(-1)
else: print(*arr)
