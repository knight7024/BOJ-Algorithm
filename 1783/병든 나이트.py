n, m = map(int, input().split())
ans = 1
if n < 2: pass
elif n < 3:
	if m < 9: ans += int((m - 1) / 2)
	else: ans = 4
else:
	if m < 5: ans = m
	elif m == 5: ans = 4
	else: ans += m - 3
print(ans)
