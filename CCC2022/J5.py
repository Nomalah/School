N = int(input())
T = int(input())
trees = []
for i in range(T):
    x, y = [int(x) for x in input().split()]
    trees.append({"x": x, "y": y})

topLeft = {"x": 1, "y": 1}
bottomRight = {"x": N, "y": N}
