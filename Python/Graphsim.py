ylist=[]
xlist=[]
plot=1
nop=int(input("Number of points: "))
while not nop==0:
    ylist.append(int(input("Y corrdinate: ")))
    xlist.append(int(input("X corrdinate: ")))
    nop=nop-1
print("y")
if ylist.count(max(ylist))==1:
    co=[max(ylist),xlist[ylist.index(max(ylist))]]
    print (co)
else:
    ylist.remove[0]
    xlist2=[]
    while not z==ylist.count(max(ylist)):
        if ylist[z]==max(ylist):
            xlist2=[xlist[z]]
        z+=1



