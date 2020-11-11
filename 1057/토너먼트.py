from math import ceil

n, k, y = map(int, input().split())
rnd = 1
while True:
	if k > y and k == y + 1 and k % 2 == 0:
		print(rnd)
		break
	elif k < y and y == k + 1 and y % 2 == 0:
		print(rnd)
		break
	k = ceil(k / 2)
	y = ceil(y / 2)
	rnd += 1
