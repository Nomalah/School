# assign_1_5_equation.py
# Tyseer Toufiq 
# 2021/04/22
# This program takes integers m and n where n is between 1 and 20 and m is between -20 and 20 
# and finds all true forms of the mathematical statement (1 − 2 − 3 + 4 = 0.) where m is the 
# right side of the equation and the left side is from 1 to n 

from itertools import permutations # Imports permutations 

n = 0 
m = -200 

count = 0 # Counter for the number of possible True Statements



key = False # Key for input validation
while not key: # Run while key is set to false
    if (n == 0): # If n is set to 0 (This is done by deafault)
        print("Enter an integer between 1 and 20")
        n = int(input()) # Take user input for n
        if (n > 20 or n < 1): # If n is greater than 20 or smaller than 1 
            n = 0 # Set n back to 0
            print("Make sure you entered an integer and that it is between 1 and 20") 

    elif (m == -200): # Input valadation for m
        print("Enter an integer between -20 and 20")
        m = int(input()) # Take in user input 
        if (m > 20 or m < -20):  # If m is greater than 20 or less than - 20
            m = -200 # Set m to -200
            print("Make sure you entered an integer and that it is between -20 and 20") 

    elif ((n > 20 or n > 1) and (m < 20 or m > -20)): # When both m and n are good
        key = True # Set key to true breaking while loop


#-4 -3 -2 1 2 3 4 
numbers = [x for x in range(-n, n+1)]  # Build an array of numbers from -n to n+1
numbers.remove(-1) # Remove -1 since its never in out equation
numbers.remove(0) # Remove 0 since its never in out equation

allPermutations = permutations(numbers, n)  # Find all permutations for n, stores them in a list of tuples of n size
#  2 1 -3 -4

def answerChecker(tuple): # Function for checking if the tuple sums up to our answer (m) and printing the equation
    
    total = sum (list(tuple)) # variable for sum of the tuple
    if (m == total):    # If the sum of the tuple is equal to m 
        tupleArray = [x for x in tuple]  # Store whatever is in the tuple in an array
        equation = ["+{}".format(x) if x>0 and x != 1 else x for x in tupleArray] # Build a new array putting in 1, then all negative values and a + string beside all positive numbers
        print("".join(str(num) for num in equation) + "=" + str(total)) # Print all numbers in equation array, printing the equation as a string
        return True # Return true
                
    

for tuple in list(allPermutations):   
  # For loop that loops through the tuple object, and makes sure that all the numbers are in sequential order
  # This means 1 in front then 2 or -2 then 3 or -3 and so on

    if (len(tuple) == 1): # If the length of the tuple is 1
        if (tuple[0] == 1):  # Tuple index zero must be equal to 1, so discard all the other permutations
            if (answerChecker(tuple)): # If answerCkecker returns true then add one to the count of valid answers
                count += 1  
      

# The remainder of this absurdly long for loop ensures that the next value is 2 or -2, then 3 or -3  
# computing all possible numbers in sequential order, and if a match is found through the answerChecker() 
# function increment the count up by 1
 
    elif (len(tuple) == 2):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2)):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 3):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3)):   
            if (answerChecker(tuple)): 
                count += 1  

         
    elif (len(tuple) == 4):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4)):   
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 5):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5)):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 6):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6)):  
            if (answerChecker(tuple)): 
                count += 1  

            

    elif (len(tuple) == 7):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7)):  
            if (answerChecker(tuple)): 
                count += 1  
                
            
    elif (len(tuple) == 8):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8)):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 9):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9)):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 10):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10)):  
            if (answerChecker(tuple)): 
                count += 1   


    elif (len(tuple) == 11):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11)):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 12):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12)):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 13):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12) and (tuple[12] == 13 or tuple[12] == -13)):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 14):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12) and (tuple[12] == 13 or tuple[12] == -13) and (tuple[13] == 14 or tuple[13] == -14)):  
            if (answerChecker(tuple)): 
                count += 1   


    elif (len(tuple) == 15):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12) and (tuple[12] == 13 or tuple[12] == -13) and (tuple[13] == 14 or tuple[13] == -14) and (tuple[14] == 15 or tuple[14]== -15)):  
            if (answerChecker(tuple)): 
                count += 1   
                

    elif (len(tuple) == 16):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12) and (tuple[12] == 13 or tuple[12] == -13) and (tuple[13] == 14 or tuple[13] == -14) and (tuple[14] == 15 or tuple[14] == -15) and (tuple[15] == 16 or tuple[15] == -16)):  
            if (answerChecker(tuple)): 
                count += 1  
 

    if (len(tuple) == 17):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12) and (tuple[12] == 13 or tuple[12] == -13) and (tuple[13] == 14 or tuple[13] == -14) and (tuple[14] == 15 or tuple[14] == -15) and tuple[15] == 16 or tuple[15] == -16) and (tuple[16] == 17 or tuple[16] == -17):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 18):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12) and (tuple[12] == 13 or tuple[12] == -13) and (tuple[13] == 14 or tuple[13] == -14) and (tuple[14] == 15 or tuple[14] == -15) and tuple[15] == 16 or tuple[15] == -16) and (tuple[16] == 17 or tuple[16] == -17) and (tuple[17] == 18 or tuple[17] == -18):  
            if (answerChecker(tuple)): 
                count += 1  


    elif (len(tuple) == 19):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12) and (tuple[12] == 13 or tuple[12] == -13) and (tuple[13] == 14 or tuple[13] == -14) and (tuple[14] == 15 or tuple[14] == -15) and tuple[15] == 16 or tuple[15] == -16) and (tuple[16] == 17 or tuple[16] == -17) and (tuple[17] == 18 or tuple[17] == -18) and (tuple[18] == 19 or tuple[18] == -19):  
            if (answerChecker(tuple)): 
                count += 1   


    elif (len(tuple) == 20):
        if (tuple[0] == 1 and (tuple[1] == 2 or tuple[1] == -2) and (tuple[2] == 3 or tuple[2] == -3) and (tuple[3] == 4 or tuple[3] == -4) and (tuple[4] == 5 or tuple[4] == -5) and (tuple[5] == 6 or tuple[5] == -6) and (tuple[6] == 7 or tuple[6] == -7) and (tuple[7] == 8 or tuple[7] == -8) and (tuple[8] == 9 or tuple[8] == -9) and (tuple[9] == 10 or tuple[9] == -10) and (tuple[10] == 11 or tuple[10] == -11) and (tuple[11] == 12 or tuple[11] == -12) and (tuple[12] == 13 or tuple[12] == -13) and (tuple[13] == 14 or tuple[13] == -14) and (tuple[14] == 15 or tuple[14] == -15) and tuple[15] == 16 or tuple[15] == -16) and (tuple[16] == 17 or tuple[16] == -17) and (tuple[17] == 18 or tuple[17] == -18) and (tuple[18] == 19 or tuple[18] == -19) and (tuple[19] == 20 or tuple[19] == -20):  
            if (answerChecker(tuple)): 
                count += 1  

print("Number of True Statements!: " + str(count)) # After long for loop output the number of tuples that met required conditions
    