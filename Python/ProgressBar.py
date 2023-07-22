from time import sleep
import sys
def progressbar(pro, maxval):
        sys.stdout.write('\r')
        # the exact output you're looking for:
        sys.stdout.write("[%-100s] {} Percent".format((int(pro/maxval*10000))/100) % ('='*int(pro/maxval*100)))
        sys.stdout.flush()
f = open("ftblauncher.txt","w")
record=[0,0]
from datetime import datetime as dt
try: input = raw_input
except: pass
c=int(input("Min number value: "))
a=int(input("Max number value: "))
y=c
x=c
start = dt.now()
while not y==a+1:
    z=0
    f.write("\n:"+str(y)+", ")
    while not x==1:
        if x%2==1:
            x=3*x+1
            z+=1
            f.write(str(x)+", ")
        else:
                    x/=2
                    z+=1
                    f.write(str(x)+", ")
    if record[0]<z:
        record=[]
        record.append(z)
        record.append(y)
    x=y+1
    progressbar(y, a)
    y+=1

print ('\nFinal Record')
print (record)
seconds = (dt.now() - start).total_seconds()
print("You took {} seconds ".format(seconds))
print("To compute up to {} .".format(a))
print("Starting from {} .".format(c))
f.close()
