// Written by Dallas Hart on 2023-01-11
// This program belongs to Assignment 1 in ENGG*1420 at UOG
// Purpose: Find the sum of divisors of a number, check if a 
// number is perfect, and find all perfect numbers < 10000

#include <stdio.h>

// Question 4
int sumOfDivisors(int n)
{
    int sum = 0;
    // Check all potential divisors (1 -> N)
    for (int i = 1; i <= n; i++)
    {
        // Check if remainder is 0
        if (n % i == 0)
        {
            sum += i; // Add divisor to sum
        }
    }
    return sum;
}

// Question 5
int isPerfectNumber(int n)
{
    // A number is a perfect number if the sum of 
    // it's divisors, excluding itself, equals itself
    return (sumOfDivisors(n) - n) == n;
}

// Question 6
int main()
{
    // Loop through numbers 9999 -> 1 and check if they're perfect numbers
    for (int i = 9999; i > 0; i--)
    {
        if (isPerfectNumber(i))
        {
            printf("%d is a perfect number!\n", i);
        }
    }
}