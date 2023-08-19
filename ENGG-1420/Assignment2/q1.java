// Written by Dallas Hart on 2023-01-16
// This program belongs to Assignment 2 in ENGG*1420 at UOG
// Purpose: print all prime numbers less then 10,000 with "while" and "if-else"

class Question1
{   
    // Function to check if a given number is a prime number
    public static boolean isPrimeNumber(int i)
    {
        // two is the first possible factor (1 is always divisible)
        int possibleFactor = 2;
        while (possibleFactor < i)
        {
            // Check if the factor divides cleanly
            if (i % possibleFactor == 0)
            {
                // possibleFactor is a factor, and thus makes i a composite number
                return false;
            }
            possibleFactor++;
        }
        // There are no factors other then 1 and i
        return true;
    }

    public static void main(String[] args)
    {
        // Test all numbers between 2 and 10000 (skip 1 because it is not a prime number)
        int i = 2;
        while (i < 10000)
        {
            // Use the function to determine primeness
            if (isPrimeNumber(i))
            {
                System.out.printf("%d is a prime number!%n", i);
            }
            i++;
        }
    }
}
