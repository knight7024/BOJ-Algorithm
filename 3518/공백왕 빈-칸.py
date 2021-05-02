import sys
arr = []
maxLen = 0
for line in sys.stdin:
	arr.append(line.strip().split())
	maxLen = max(maxLen, len(arr[-1]))
for i in range(maxLen - 1):
	# 가장 긴 단어수 찾는다.
	maxWord = 0
	for j in arr:
		if i >= len(j): continue
		maxWord = max(maxWord, len(j[i]))
	# 다른 단어들에는 가장 긴 단어수만큼 공백 채워준다.
	for j in arr:
		if i >= len(j): continue
		j[i] = j[i].ljust(maxWord)
for i in range(len(arr)): print(' '.join(arr[i]).rstrip())
