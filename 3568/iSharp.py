s = input().split(' ')
template = s[0]
for i in range(1, len(s)):
	s[i] = s[i].rstrip(',;')
	v = s[i].rstrip('[]&*')
	op = s[i][len(v):]
	rev = ''
	for j in range(len(op), 0, -1):
		if op[j - 1] == '*':
			rev += '*'
		elif op[j - 1] == '&':
			rev += '&'
		elif op[j - 1] == '[':
			continue
		else:
			rev += '[]'
	print('%s%s %s;' % (template, rev, s[i][0:len(v)]))
