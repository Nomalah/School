# a1_4_infiniteSequence
# Dallas Hart
#
# Calculates the fraction of H(n) = 1/1 + 1/2 + 1/3 + 1/4 + ... + 1/n

n = 1

# Error checking
print("Please input an integer")
exitFlag = False
while not exitFlag:
    n = input()
    try:
        exitFlag = int(n) > 0
    except ValueError:
        # bruh mode
        continue
n = int(n)

# Create fraction
numerator = 0
denomonator = 1
for n in range(1, n+1):
    prevDenomonator = denomonator
    denomonator *= n
    numerator *= n
    numerator += prevDenomonator

print(numerator, "/", denomonator)

# ******s-iMac:Assignment Code ******$ python3 a1_4_infiniteSequence.py
# Please input an integer
# 7
# 13068 / 5040
