x=1
y=1
sizesol=[]
Storage = open("RawCollatz.txt","w")
av = open("AvCollatz.txt","w")
from datetime import datetime as dt
try: input = raw_input
except: pass
a=float(input("Max number value: "))
start = dt.now()
while not y==a+1:
    print(y, end = "\r")
    z=0
    while not x==1:
        if x%2==1:
            x=3*x+1
            z+=1
        else:
            x/=2
            z+=1
    sizesol.append(z)
#print(str(int(z)),end="\r")
    av.write("\n"+str(round(sum(sizesol))/len(sizesol)))
    Storage.write("\n"+str(int(z)))
    x=y+1
    y+=1
seconds = (dt.now() - start) .total_seconds()
print("You took {} seconds ".format(seconds))
print("To compute up to {}.".format(a))
Storage.close()
av.close()
