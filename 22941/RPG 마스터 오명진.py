from math import ceil
import sys
input = sys.stdin.readline

hpW, atkW, hpD, atkD = map(int, input().split())
p, s = map(int, input().split())
needAtkCntW, needAtkCntD = (hpD - p) // atkW, int(ceil(hpW / atkD))
if 1 <= hpD - needAtkCntW * atkW <= p:
	hpD = hpD - needAtkCntW * atkW + s
	needAtkCntW += int(ceil(hpD / atkW))
elif 1 <= hpD - (needAtkCntW + 1) * atkW <= p:
	hpD = hpD - (needAtkCntW + 1) * atkW + s
	needAtkCntW += int(ceil(hpD / atkW)) + 1
elif needAtkCntW == 0:
	pass
elif hpD <= (needAtkCntW + 1) * atkW:
	needAtkCntW += 1
print("Victory!" if needAtkCntW <= needAtkCntD else "gg")
