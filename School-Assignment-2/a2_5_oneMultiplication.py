# a2_5_oneMultiplication
# Dallas Hart
#
# Time complexity is N log log N and bounded by the sieve of eratosthenes
import sys
# Error checking
"""
print("Please input a positive integer: ", end="")
exitFlag = False
while not exitFlag:
    n = input()
    try:
        exitFlag = int(n) > 0
    except ValueError:
        # bruh mode
        print("Please input a positive integer: ", end="")
"""
n = int(sys.argv[1])

# Sieve of Eratosthenes
primeArr = [True] * (n + 1)
primes = []
primeFactorization = {}
for i in range(2, n + 1):
    if primeArr[i]:
        primes.append(i)
        primeFactorization[i] = 0
        for j in range(i + i, n+1, i):
            primeArr[j] = False

total = 0

#print("The minimum number of ones used to create", n, "is", end=" ")

# Compute prime factorization of n (subtract one if n is already prime)
if primeArr[n]:
    n -= 1
    total += 1


temp = n        

# For every prime (largest to smallest), find the number of times the divides temp
for i in range(len(primes) - 1, -1, -1):
    while (temp % primes[i] == 0):
        temp //= primes[i]
        primeFactorization[primes[i]] += 1
    if primeFactorization[primes[i]] != 0:
        # If the prime had divided at any point, compress the prime and add the new factorization to the old factorization
        if (primes[i] == 2):
            total += 2 * primeFactorization[primes[i]]
        else:
            # Add the prime factorization of i-1 to the total
            primeSub1Temp = primes[i] - 1
            total+=primeFactorization[primes[i]]
            for j in range(i, -1, -1):
                while (primeSub1Temp % primes[j] == 0):
                    primeSub1Temp //= primes[j]
                    primeFactorization[primes[j]] += primeFactorization[primes[i]]
            primeFactorization[primes[i]] = 0

    
# Edge case where n == 2
if n == 1:
    total += 1

print(total, end="")

"""
******s-iMac:assignment code ******$ pypy3 a2_5_oneMultiplication.py
Please input a positive integer: 1234567
The minimum number of ones used to create 1234567 is 42
******s-iMac:assignment code ******$ pypy3 a2_5_oneMultiplication.py
Please input a positive integer: 98234798
The minimum number of ones used to create 98234798 is 60
******s-iMac:assignment code ******$ pypy3 a2_5_oneMultiplication.py
Please input a positive integer: 14
The minimum number of ones used to create 14 is 8
"""