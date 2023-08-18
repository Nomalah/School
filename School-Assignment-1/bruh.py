# assign_1_5_equation.py
# Tyseer Toufiq 
# 2021/04/22
# This program takes integers m and n where n is between 1 and 20 and m is between -20 and 20 
# and finds all true forms of the mathematical statement (1 − 2 − 3 + 4 = 0.) where m is the 
# right side of the equation and the left side is from 1 to n 

# Imports Numpy

n = None # set n = None
m = None # set m = None 
n = int(input()) # Take user input for n  
m = int(input()) # Take in user input 
            
def evaluate(size, toEvaluate, target, max):
    total = 0
    for i in range(1, max+1):
        if size & toEvaluate:
            total -= i
        else:
            total += i
        size >>= 1
    return target == total


def visualize(size, toEvaluate, target, max):
    for i in range(1, max+1):
        if size & toEvaluate:
            print("-", i, end=" ")
        else:
            print("+", i, end=" ")
        size >>= 1
    print("=", target)

solutions = 0
size = 1 << (n - 1)
for i in range(size-1, 0, -1):
    if evaluate(size, i, m, n):
        visualize(size, i, m, n)
        solutions += 1
        
print(solutions)
