n = int(input())
mList = []
pList = []
for i in range(n):
    m = int(input())
    if m > 0:
        pList.append(m)
    elif m <= 0:
        mList.append(m)
pList.sort(reverse=True)
mList.sort()
i = 0
sum = 0
while i < len(pList):
    if i + 1 < len(pList):
        if pList[i] * pList[i + 1] > pList[i] + pList[i + 1]:
            sum += pList[i] * pList[i + 1]
        else:
            sum += pList[i] + pList[i + 1]
        i += 1
    else:
        sum += pList[i]
    i += 1
i = 0
while i < len(mList):
    if i + 1 < len(mList):
        sum += mList[i] * mList[i + 1]
        i += 1
    else:
        sum += mList[i]
    i += 1
print(sum)
