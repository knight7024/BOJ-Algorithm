from itertools import permutations

k = int(input())
arr = input().split()

num = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
p = permutations(num, len(arr) + 1)

maxNum, minNum = -1, 9876543210
for i in p:
	flag = True
	for j in range(len(arr)):
		if arr[j] == '<' and i[j] < i[j + 1]: continue
		elif arr[j] == '>' and i[j] > i[j + 1]: continue
		else:
			flag = False
			break
	
	if flag:
		nowNum = ''.join(map(str, i))
		if int(maxNum) < int(nowNum): maxNum = nowNum
		if int(minNum) > int(nowNum): minNum = nowNum
		pass

print(maxNum, minNum)
