Storage = open("Collatz.txt","w")
record=[0,0]
from datetime import datetime as dt
try: input = raw_input
except: pass
c=float(input("Min number value: "))
a=float(input("Max number value: "))
y=c
x=c
start = dt.now()
while not y==a+1:
    print (y)
    z=0
    Storage.write("\n:"+str(int(y))+",")
    while not x==1:
        if x%2==1:
            x=3*x+1
            z+=1
            Storage.write(str(int(x))+",")
        else:
            x/=2
            z+=1
            Storage.write(str(int(x))+",")
    if record[0]<z:
        record=[]
        record.append(z)
        record.append(y)
        print ('New record')
        print (record)
    x=y+1
    y+=1
print ('Final Record')
print (record)
seconds = (dt.now() - start).total_seconds()
print("You took {} seconds ".format(seconds))
print("To compute up to {} .".format(a))
print("Starting from {} .".format(c))
Storage.close()
