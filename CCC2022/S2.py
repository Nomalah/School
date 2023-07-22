sameCount = int(input())
sameMap = {}
for i in range(sameCount):
    a, b = input().split()
    if a in sameMap:
        sameMap[a][b] = False
    else:
        sameMap[a] = { b: False }
    if b in sameMap:
        sameMap[b][a] = False
    else:
        sameMap[b] = { a: False }
    
difCount = int(input())
difMap = {}
for i in range(difCount):
    a, b = input().split()
    if a in difMap:
        difMap[a][b] = True
    else:
        difMap[a] = { b: True }
    if b in difMap:
        difMap[b][a] = True
    else:
        difMap[b] = { a: True }

groupCount = int(input())
sameGroupCount = 0
violateCount = 0
for i in range(groupCount):
    a, b, c = input().split()
    if a in difMap and b in difMap[a]:
        violateCount += 1
    if a in difMap and c in difMap[a]:
        violateCount += 1
    if b in difMap and c in difMap[b]:
        violateCount += 1

    
    
    if a in sameMap and b in sameMap[a]:
        sameGroupCount += 1
    if a in sameMap and c in sameMap[a]:
        sameGroupCount += 1
    if c in sameMap and b in sameMap[c]:
        sameGroupCount += 1


print(violateCount + sameCount - sameGroupCount)
