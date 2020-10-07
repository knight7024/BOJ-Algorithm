from sys import stdin

t = int(input())
while t:
	n = int(input())
	dial = []
	dialDic = set()
	for _ in range(n):
		tel = stdin.readline().strip()
		dial.append([len(tel), tel])
		dialDic.add(tel)

	dial.sort()
	
	flag = False
	for i in range(1, len(dial)):
		if flag:
			break
		for j in range(len(dial[i][1])):
			if dial[i][1][:j] in dialDic:
				flag = True
				break
	
	print('NO' if flag else 'YES')
	t -= 1
