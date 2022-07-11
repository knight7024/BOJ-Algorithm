h = int(input()) + 1
dp = [1]
p = 1
for i in range(3, h + 1):
	p *= 2
	if h & 1 == i & 1: dp.append(dp[-1] + p)
print(dp[-1])
