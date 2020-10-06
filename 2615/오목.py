import sys
sys.setrecursionlimit(10 ** 6)

lastType = -1

def track(r, c, color, type, depth):
	global lastType
	result = False

	# Base Case
	if depth > 5:
		return False
	
	# 처음이면
	if type == -1:
		if c + 1 < 19 and board[r][c + 1] == color:
			result |= track(r, c + 1, color, 0, depth + 1)
		if r + 1 < 19 and c + 1 < 19 and board[r + 1][c + 1] == color:
			result |= track(r + 1, c + 1, color, 1, depth + 1)
		if r + 1 < 19 and board[r + 1][c] == color:
			result |= track(r + 1, c, color, 2, depth + 1)
		if r + 1 < 19 and c - 1 >= 0 and board[r + 1][c - 1] == color:
			result |= track(r + 1, c - 1, color, 3, depth + 1)
	# 3시 방향 →
	elif type == 0:
		# 9시
		if j - 1 >= 0 and board[i][j - 1] == color:
			return False
		if c + 1 < 19 and board[r][c + 1] == color:
			return track(r, c + 1, color, type, depth + 1)
	# 5시 방향 ↘
	elif type == 1:
		# 11시
		if i - 1 >= 0 and j - 1 >= 0 and board[i - 1][j - 1] == color:
			return False
		if r + 1 < 19 and c + 1 < 19 and board[r + 1][c + 1] == color:
			return track(r + 1, c + 1, color, type, depth + 1)
	# 6시 방향 ↓
	elif type == 2:
		# 12시
		if i - 1 >= 0 and board[i - 1][j] == color:
			return False
		if r + 1 < 19 and board[r + 1][c] == color:
			return track(r + 1, c, color, type, depth + 1)
	# 7시 방향 ↙
	# 가장 왼쪽에 있는 수가 가장 아래에 있는 수가 되므로 주의한다.
	elif type == 3:
		# 1시
		if i - 1 >= 0 and j + 1 < 19 and board[i - 1][j + 1] == color:
			return False
		if r + 1 < 19 and c - 1 >= 0 and board[r + 1][c - 1] == color:
			return track(r + 1, c - 1, color, type, depth + 1)
			
	if depth == 5:
		lastType = type
		return True

	return result


board = []
for i in range(19):
	board.append(list(map(int, input().split())))

flag = False
for i in range(19):
	if flag:
		break
	for j in range(19):
		color = board[i][j];
		if color:			
			if track(i, j, color, -1, 1):
				print(color)
				if lastType != 3:
					print(i + 1, j + 1)
				else:
					print(i + 5, j - 3)
				flag = True
				break
				
if not flag:
	print(0)
