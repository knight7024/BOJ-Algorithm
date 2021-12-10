def recur(idx):
    eq.append(str(idx + 1))
    if idx == n - 1:
        evalStr = ''.join(map(lambda x : '' if x == ' ' else x, eq))
        if not eval(evalStr):
            print(''.join(eq))
        return

    eq.append(' ')
    recur(idx + 1)
    eq.pop()
    eq.pop()

    eq.append('+')
    recur(idx + 1)
    eq.pop()
    eq.pop()

    eq.append('-')
    recur(idx + 1)
    eq.pop()
    eq.pop()
    


t = int(input())
while t:
    n = int(input())
    eq = []
    recur(0)
    print()
    t -= 1
