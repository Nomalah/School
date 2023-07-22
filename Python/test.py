# function to check if the number is
# prime or not
import math
primes = [2]
f = open("info.txt","w")
def isPrime(n) :
    # Corner cases
    if (n <= 1) :
        return False
    if (n <= 3) :
        return True

    # This is checked so that we can skip
    # middle five numbers in below loop
    if (n % 2 == 0 or n % 3 == 0) :
        return False
    p=math.sqrt(n)
    for i in primes :
        if n % i == 0 :
            return False
        if p < i :
            break
        if i > 44721:
            break

    return True

# print all prime numbers
# less than equal to N
def printPrime(n):
    for i in range(3, n + 1):
        if isPrime(i):
            primes.append(i)
            f.write(str(i)+",")
            print (i, end =",")

n = 2000000000
printPrime(n)
f.close()
