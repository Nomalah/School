// Written by Dallas Hart on 2023-01-11
// This program belongs to Assignment 1 in ENGG*1420 at UOG
// Purpose: print a 4 digit number in reverse

#include <stdio.h>

int main()
{   
    // Only allow 4 digit numbers from input to continue
    int num = 0;
    while (num < 1000 || num > 9999)
    {
        printf("Please input 4 digit number: ");
        scanf("%d", &num);
    }

    // Print digits in reverse
    printf("%d in reverse is: ", num);
    while (num != 0)
    {
        printf("%d", num % 10); // Get last digit in number
        num /= 10; // Remove the last digit from number
    }
    printf("\n");
    return 0;
}