# 에라토스테네스의 체로 소수 구하기
def getPrimes(n):
	global sieve
	global primes
	for i in range(2, n + 1):
		if not sieve[i]:
			continue
		for j in range(i * i, n + 1, i):
			sieve[j] = False
		primes.append(i)

n = int(input())
sieve = [True for _ in range(n + 1)]
primes = []
getPrimes(n)

# 투 포인터
start = 0
end = start + 1
lenPrime = len(primes)
ans = 0
sum = 0

if start < lenPrime:
	sum += primes[start]
if end < lenPrime:
	sum += primes[end]

while True:
	if sum == n:
		ans += 1
		if end + 1 < lenPrime:
			end += 1
			sum += primes[end]
		else:
			break;
	elif sum > n:
		sum -= primes[start]
		start += 1
	elif sum < n:
		if end + 1 < lenPrime:
			end += 1
			sum += primes[end]
		else:
			break

print(ans)
