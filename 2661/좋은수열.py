from sys import exit

def isGoodArray(arr):
	n = len(arr)
	for i in range(n):
		for j in range(1, n):
			start, end = i, i + j
			if end >= n: break
			if arr[start:end] == arr[start+j:end+j]: return False
	return True

def backtracking(r, arr):
	if not isGoodArray(arr): return
	if not r:
		print(arr)
		exit(0)
		return
	backtracking(r - 1, arr + '1')
	backtracking(r - 1, arr + '2')
	backtracking(r - 1, arr + '3')

n = int(input())
backtracking(n, '')
