// a2_2_partitions
// Dallas Hart
//
// Program to print all partitions of n of length r

#include <iostream>
#include <vector>

#include "NMLH_error_checking.hpp"

void recursive(std::vector<int> &v, int totalLeft, int itemsLeft, int previous, int itemIndex)
{
    if (itemsLeft == 0)
    {
        // If the total adds up to n
        if (totalLeft == 0)
        {
            for (auto &x : v)
            {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }
    else
    {
        // Solution goes smallest to largest which means the all items after the current, must be able to fit the size of the current value
        for (std::size_t i = previous; i <= totalLeft / itemsLeft; i++)
        {
            v[itemIndex] = i;
            recursive(v, totalLeft - i, itemsLeft - 1, i, itemIndex + 1);
        }
    }
}

int main()
{
    int n = 0, r = 0;
    n = input<int>("Enter an integer n: ");
    if (n <= 0)
    {
        std::cout << "0 solutions";
        return 0;
    }

    do
    {
        r = input<int>("Enter an integer r: ");
    } while (r <= 0 || r > n);

    // Vector of size r to store data
    std::vector<int> v;
    v.resize(r);
    recursive(v, n, r, 1, 0);

    return 0;
}

/*
******s-iMac:Assignment code ******$ ./out
Enter an integer n: 7
Enter an integer r: 3
1 1 5 
1 2 4 
1 3 3 
2 2 3 
******s-iMac:Assignment code ******$ ./out
Enter an integer n: 20
Enter an integer r: 5
1 1 1 1 16 
1 1 1 2 15 
1 1 1 3 14 
1 1 1 4 13 
1 1 1 5 12 
1 1 1 6 11 
1 1 1 7 10 
1 1 1 8 9 
1 1 2 2 14 
1 1 2 3 13 
1 1 2 4 12 
1 1 2 5 11 
1 1 2 6 10 
1 1 2 7 9 
1 1 2 8 8 
1 1 3 3 12 
1 1 3 4 11 
1 1 3 5 10 
1 1 3 6 9 
1 1 3 7 8 
1 1 4 4 10 
1 1 4 5 9 
1 1 4 6 8 
1 1 4 7 7 
1 1 5 5 8 
1 1 5 6 7 
1 1 6 6 6 
1 2 2 2 13 
1 2 2 3 12 
1 2 2 4 11 
1 2 2 5 10 
1 2 2 6 9 
1 2 2 7 8 
1 2 3 3 11 
1 2 3 4 10 
1 2 3 5 9 
1 2 3 6 8 
1 2 3 7 7 
1 2 4 4 9 
1 2 4 5 8 
1 2 4 6 7 
1 2 5 5 7 
1 2 5 6 6 
1 3 3 3 10 
1 3 3 4 9 
1 3 3 5 8 
1 3 3 6 7 
1 3 4 4 8 
1 3 4 5 7 
1 3 4 6 6 
1 3 5 5 6 
1 4 4 4 7 
1 4 4 5 6 
1 4 5 5 5 
2 2 2 2 12 
2 2 2 3 11 
2 2 2 4 10 
2 2 2 5 9 
2 2 2 6 8 
2 2 2 7 7 
2 2 3 3 10 
2 2 3 4 9 
2 2 3 5 8 
2 2 3 6 7 
2 2 4 4 8 
2 2 4 5 7 
2 2 4 6 6 
2 2 5 5 6 
2 3 3 3 9 
2 3 3 4 8 
2 3 3 5 7 
2 3 3 6 6 
2 3 4 4 7 
2 3 4 5 6 
2 3 5 5 5 
2 4 4 4 6 
2 4 4 5 5 
3 3 3 3 8 
3 3 3 4 7 
3 3 3 5 6 
3 3 4 4 6 
3 3 4 5 5 
3 4 4 4 5 
4 4 4 4 4 
******s-iMac:Assignment code ******$ ./out
Enter an integer n: 2
Enter an integer r: 1
2 
*/