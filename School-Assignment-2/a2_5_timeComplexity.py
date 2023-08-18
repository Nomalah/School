import sys
import subprocess
import random

maxNum = 10 ** 8
for i in range(1, int(sys.argv[1])):
    x = i
    p = subprocess.Popen(["time", "pypy3", "a2_5_oneMultiplication.py", str(x)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print(p.stdout.readlines()[0].decode("ascii"))
    #timeOutput = p.stderr.readlines()[0].decode("ascii").split()
    #print(x, float(timeOutput[2]) + float(timeOutput[4]))