// Written by Dallas Hart on 2023-01-16
// This program belongs to Assignment 2 in ENGG*1420 at UOG
// Purpose: print all prime numbers less then 10,000 with "for" and "switch-case"

class Question2
{
    // Function to check if a given number is a prime number
    public static int isPrimeNumber(int i)
    {
        // two is the first possible factor (1 is always divisible)
        for (int possibleFactor = 2; possibleFactor < i; possibleFactor++)
        {
            // Check if the factor divides cleanly
            switch (i % possibleFactor)
            {
                case 0:
                    // possibleFactor is a factor, and thus makes i a composite number
                    return 0;
            }
        }
        // There are no factors other then 1 and i
        return 1;
    }

    public static void main(String[] args)
    {
        // Test all numbers between 2 and 10000 (skip 1 because it is not a prime number)
        for (int i = 2; i < 10000; i++)
        {
            // Use the function to determine primeness
            switch (isPrimeNumber(i))
            {
                case 1:
                    System.out.printf("%d is a prime number!%n", i);
                    break;
            }
        }
    }
}
