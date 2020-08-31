expression = input()
sum = 0
expressionList = expression.split('-')
sum += eval("+".join(token.lstrip('0') for token in expressionList[0].split('+')))
for i in range(1, len(expressionList)):
	sum -= eval("+".join(token.lstrip('0') for token in expressionList[i].split('+')))
print(sum)
