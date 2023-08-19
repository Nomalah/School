/******************************************************************************

ENGG1410 F22
LAB 4 - Tuesday 8:30 AM Section
Prepared by Somya Sharma

Task 1 - Fix the broken code

This code should print the output mentioned below. After you are
done move on to Task 2 of this lab.

Output:

        1
      1   2
    1   2   3
  1   2   3   4
1   2   3   4   5

*******************************************************************************/
#include <stdio.h>

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        for (int k = 10 - i *2; k > 0; k--)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("%d   ", j);
        }
        printf("\n");
    }
}