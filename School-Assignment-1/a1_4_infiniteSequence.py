# a1_4_infiniteSequence
# Dallas Hart
#
# Calculates the fraction of H(n) = 1/1 + 1/2 + 1/3 + 1/4 + ... + 1/n

n = 1

# Error checking
print("Please input a positive integer")
exitFlag = False
while not exitFlag:
    n = input()
    try:
        exitFlag = int(n) > 0
    except ValueError:
        # bruh mode
        print("Enter a positive integer!")
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
# ******s-iMac:Assignment Code ******$ python3 a1_4_infiniteSequence.py
# Please input a positive integer
# 123
# 65510601319252760167086019039511888398134529907924600438791664454987039454840340187645544786008198421138246428404933431638916464209186096368924584584340399155978957706138526679040000000000000000000000000000 / 12146304367025329675766243241881295855454217088483382315328918161829235892362167668831156960612640202170735835221294047782591091570411651472186029519906261646730733907419814952960000000000000000000000000000
# ******s-iMac:Assignment Code ******$ python3 a1_4_infiniteSequence.py
# Please input a positive integer
# 50
# 136839250493597505643457826872702521913187810543371550720000000000 / 30414093201713378043612608166064768844377641568960512000000000000