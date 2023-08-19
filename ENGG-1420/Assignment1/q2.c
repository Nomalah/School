// Written by Dallas Hart on 2023-01-11
// This program belongs to Assignment 1 in ENGG*1420 at UOG
// Purpose: add, subtract or multiply two numbers

#include <stdio.h>

int main()
{
    // Get user input
    int a = 0, b = 0;
    char ch = '\0';
    printf("Please input number A: ");
    scanf("%d", &a);
    printf("Please input number B: ");
    scanf("%d", &b);
    printf("Please character ch: ");
    scanf(" %c", &ch);

    // Determine  & execute user selected operation
    if (ch == '+')
    {
        printf("%d + %d = %d\n", a, b, a+b);
    } else if (ch == '*')
    {
        printf("%d * %d = %d\n", a, b, a*b);
    } else if (ch == '-')
    {
        printf("%d - %d = %d\n", a, b, a-b);
    } else
    {
        printf("Unknown operation!\n");
    }
    return 0;
}