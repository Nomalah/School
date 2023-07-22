import numpy as np
print("Initializing")
class node1:
    def __init__(self):
        np.random.seed(1)
        self.weights = 2 * np.random.random((2,1)) - 1
    def train(self,inputs,outputs,num):
        for iteration in range(num):
            output = self.think(inputs)
            error = outputs - output
            adjustment = 0.01*np.dot(inputs.T,error)
            self.weights += adjustment
    def think(self,inputs):
        return (np.dot(inputs,self.weights))
node1=node1()
inputs = np.array([[1,2],[1,0],[0,1],[1,1]])
outputs = np.array([[8,6,5,7]]).T
TestNum = input("How many tests would you like to conduct: ")
node1.train(inputs,outputs,TestNum)
print("Testing complete.")
Number1 = input("What is the first number you would like to compute: ")
Number2 = input("What is the second number you would like to compute: ")
print("Solving in progress")
print(node1.think(np.array([Number1,Number2])))
print("Solved")
print(node1.weights)
