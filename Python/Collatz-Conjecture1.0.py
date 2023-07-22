x=1
y=1
record=[0,0]
while not y==11:
    z=0
    while not x==1:
            if x%2==1:
                    x=3*x+1
                    z+=1
            else:
                    x/=2
                    z+=1
    if z>record[1]:
        record=[]
        record.append("Hi")
        record.append("Hi")
