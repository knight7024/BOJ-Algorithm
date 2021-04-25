s = input()
arr = []
fail = False
for c in s:
	if c in '([':
		arr.append(c)
		continue
	
	popSum = 0
	if c == ')':
		while len(arr) and arr[-1].isdigit(): popSum += int(arr.pop())
		if not len(arr) or arr[-1] != '(':
			fail = True
			break
		arr.pop()
		if popSum: arr.append(str(popSum * 2))
		else: arr.append('2')
	elif c == ']':
		while len(arr) and arr[-1].isdigit(): popSum += int(arr.pop())
		if not len(arr) or arr[-1] != '[':
			fail = True
			break
		arr.pop()
		if popSum: arr.append(str(popSum * 3))
		else: arr.append('3')

answer = 0
if not fail:
	for i in arr:
		if not i.isdigit():
			answer = 0
			break
		answer += int(i)
print(answer)
