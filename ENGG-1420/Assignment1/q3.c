// Written by Dallas Hart on 2023-01-11
// This program belongs to Assignment 1 in ENGG*1420 at UOG
// Purpose:  find the largest and smallest from 5 user inputted numbers

#include <stdio.h>

int main()
{
    // Array to store user's numbers
    int a[5] = {};
    for (int i = 0; i < 5; i++)
    {
        printf("Input #%d: ", i + 1);
        scanf("%d", &a[i]); // insert into array
    }

    // At the start, the first entry is both the largest and smallest
    int smallest = a[0], largest = a[0];
    // Loop through remaining elements and find the current minimum and maximum
    for (int i = 1; i < 5; i++)
    {
        // This ternary returns the smallest of 2 numbers
        smallest = a[i] < smallest ? a[i] : smallest;
        // This ternary returns the largest of 2 numbers
        largest = a[i] > largest ? a[i] : largest;
    }
    printf("Smallest: %d\nLargest: %d\n", smallest, largest);
    return 0;
}