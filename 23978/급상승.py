import sys
input = sys.stdin.readline

def checkCost(coinCost):
    ret = 0
    for i in range(1, len(days)):
        diff = days[i] - days[i - 1]
        ret += coinCost * (coinCost + 1) // 2 if diff >= coinCost else coinCost * diff - diff * (diff - 1) // 2
    ret += coinCost * (coinCost + 1) // 2
    return ret

n, k = map(int, input().split())
days = list(map(int, input().split()))

start, end = 0, k + 1
while start + 1 < end:
    mid = (start + end) // 2
    if checkCost(mid) >= k:
        end = mid
    else:
        start = mid

print(end)
