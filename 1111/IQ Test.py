n = int(input())
arr = list(map(int, input().split()))

# 수열이 하나 뿐이라면 다음에 아무거나 나와도 되므로 A
if len(arr) == 1:
	print("A")
	quit()
# 수열이 두 개 뿐이라면
# 1. 모두 같은 수라면 a = 1 & b = 0인 경우이므로 그대로 출력
# 2. 아니라면 다음에 아무거나 나와도 되므로 A
elif len(arr) == 2:
	if arr[0] == arr[1]:
		print(arr[0])
	else:
		print("A")
	quit()
# 연속한 숫자 2개가 같은 경우라면
# a = 1 & b = 0인 경우므로 모든 순열이 같은 수여야 한다.
if not arr[1] - arr[0]:
	for i in arr:
		if i != arr[0]:
			print("B")
			quit()
	print(arr[0])
	quit()

# 그 외에는 방정식을 통해 a와 b를 구한다.
a = int((arr[2] - arr[1]) / (arr[1] - arr[0]))
b = int(arr[1] - (arr[0] * a))

for i in range(1, len(arr)):
	if arr[i] != int(a * arr[i - 1] + b):
		print("B")
		quit()

print(int(arr[-1] * a + b))
