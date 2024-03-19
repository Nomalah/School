# Imports beyond the standard python library will not
# pass the autograder!
import math
# you will likely need to write t
# his helper routine
# but it will not be tested
# returns a, s, b, t
def inverse(a, n):
    t = 0
    newt = 1
    r = n
    newr = a

    while newr != 0:
        quotient = r // newr
        (t, newt) = (newt, t - quotient * newt) 
        (r, newr) = (newr, r - quotient * newr)

    if r > 1:
        return "a is not invertible"
    if t < 0:
        t = t + n

    return t

# checks if a provided private key d is valid
#    given valid e, p, q
# To understand this check, consider (GCD CT)
def checkPrivateKey( d, e, p, q ):
    return (d * e) % ((p-1)*(q-1)) == 1

# assume p,q prime positive integers (p,q > 2)
# assume 2 < e < (p − 1)(q − 1)
# assume gcd(e, (p-1)(q-1)) = 1
# must return private key d > 0
# Hints: 
# - python has proper modulus support for negative numbers
#   ex: -1 % 5 = 4
# - You will want to use the extended Euclidean algoritm 
#   to compute the modular inverse
def genPrivateKey( e, p, q ):
    # looking to do something....
    n = p*q
    d = inverse(e, (p-1) * (q-1))
    return d

# e and n are the public key as described in the notes
# assume e and n constitute a valid public key
# message is an array of integers, of which each index
#     must be encrypted individually
# assume 0 <= message[i] < n
# you may modify message in place
# public keys are usually small so do not worry about
#       performance in this routine
# Hints: 
# - you may want to calculate an exponent iteratively
#   and apply a modulus with each iteration
def encryptRSA( message, e, n ):
    for i in range(len(message)):
        val = message[i]
        c = 1
        for j in range(e):
            c = (c * val) % n
        message[i] = c
    return message

# d, q, p is the private key as described in the notes
# assume n and d are valid
# ciphertext is an array of integers, of which each 
#     index must be decrypted individually
# you may modify ciphertext in place
# Hints:
# - naive exponentiation by d will be too slow!
# - use the extended euclidean algorithm to find the unique 
#   solution posed by the Chinese Remainder Theorem
# - watch https://www.youtube.com/watch?v=NcPdiPrY_g8
def decryptRSA( ciphertext, d, q, p):
    dp = d % (p - 1)
    dq = d % (q - 1)
    
    q_inv = 1
    z = (-1 % (p-1))
    for i in range(z):
        q_inv = (q_inv * q) % p
    
    for i in range(len(ciphertext)):
        valp = ciphertext[i] % p
        cp = 1
        for j in range(dp):
            cp = (cp * valp) % p

        valq = ciphertext[i] % q
        cq = 1
        for j in range(dq):
            cq = (cq * valq) % q

        h = (q_inv * (cp - cq)) % p
        ciphertext[i] = cq + h * q

    return ciphertext


# Testing code provided in main():
def main():
    decryptRSA([], 413, 53, 61)
    testDir = "tests/" # update this path with the path to your tests directory!
    passed = True
    with open(f"{testDir}/testKeyGen.txt") as idFile:
        args = []
        for idx, line in enumerate(idFile.readlines()):
            if idx % 2 == 0:
                args = line.split(" ")
            else:
                computedKey = genPrivateKey(int(args[0]), int(args[1]), int(args[2]))
                correctKey = int(line.split()[0])
                if checkPrivateKey(computedKey, int(args[0]), int(args[1]), int(args[2])) != 1:
                    print(f"Failed testKeyGen test, Expected: {correctKey}, Got: {computedKey}")
                    passed = False
    if passed:
        print("Passed testKeyGen tests")
    passed = True
    with open(f"{testDir}/testEncrypt.txt") as idFile:
        args = []
        for idx, line in enumerate(idFile.readlines()):
            if idx % 2 == 0:
                args = line.split(" ")
            else:
                ciphertextOut = encryptRSA( [0,1,2,3,4,5,6,7,8,9,10], int(args[0]), int(args[1]) * int(args[2]) )
                correctText = [int(i) for i in line.split(" ")]
                if ciphertextOut != correctText:
                    print(f"Failed testEncrypt test:\nExpected: ")
                    print(correctText)
                    print("Got: ")
                    print(ciphertextOut)
                    passed = False
    if passed:
        print("Passed testEncrypt tests")
    passed = True
    with open(f"{testDir}/testDecrypt.txt") as idFile:
        expected = [0,1,2,3,4,5,6,7,8,9,10]
        args = []
        for idx, line in enumerate(idFile.readlines()):
            if idx % 2 == 0:
                args = line.split(" ")
            else:
                cipherIn = [int(i) for i in line.split(" ")]
                messageOut = decryptRSA( cipherIn, int(args[0]), int(args[1]), int(args[2]) )
                if messageOut != expected:
                    print(f"Failed testDecrypt test:\nExpected: ")
                    print(expected)
                    print("Got: ")
                    print(messageOut)
                    passed = False
    if passed:
        print("Passed testDecrypt tests")
    return 0

if __name__ == '__main__':
    main()