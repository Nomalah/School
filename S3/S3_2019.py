row1 = [None if x =="X" else int(x) for x in input().split()]
row2 = [None if x =="X" else int(x) for x in input().split()]
row3 = [None if x =="X" else int(x) for x in input().split()]

added = True
while added: 
    added = False   
    if row1.count(None) == 1:
        if row1[0] is None:
            row1[0] = 2 * row1[1] - row1[2]
        elif row1[1] is None:
            row1[1] = row1[0] + (row1[2]-row1[0])//2
        else:
            row1[2] = 2 * row1[1]-row1[0]
        added = True
    if row2.count(None) == 1:
        if row2[0] is None:
            row2[0] = 2 * row2[1] - row2[2]
        elif row2[1] is None:
            row2[1] = row2[0] + (row2[2]-row2[0])//2
        else:
            row2[2] = 2 * row2[1]-row2[0]
        added = True
    if row3.count(None) == 1:
        if row3[0] is None:
            row3[0] = 2 * row3[1] - row3[2]
        elif row3[1] is None:
            row3[1] = row3[0] + (row3[2]-row3[0])//2
        else:
            row3[2] = 2 * row3[1]-row3[0]
        added = True
    if row[]

print(" ".join([str(x) for x in row1]))
print(" ".join([str(x) for x in row2]))
print(" ".join([str(x) for x in row3]))
