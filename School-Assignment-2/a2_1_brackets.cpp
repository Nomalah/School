// a2_1_brackets
// Dallas Hart
//
// Program to print all balanced brackets with n pairs of brackets.

#include <iostream>
#include "NMLH_error_checking.hpp"

void printBrackets(std::string inputString, int maxBracketPairs, int numOfOpenBrackets, int numOfCloseBrackets)
{
    // Print completed solution
    if (numOfCloseBrackets == maxBracketPairs)
    {
        std::cout << inputString << std::endl;
    }
    else
    {
        // Close a bracket pair
        if (numOfOpenBrackets > numOfCloseBrackets)
        {
            printBrackets(inputString + ")", maxBracketPairs, numOfOpenBrackets, numOfCloseBrackets + 1);
        }

        // Open a new bracket pair
        if (numOfOpenBrackets < maxBracketPairs)
        {
            printBrackets(inputString + "(", maxBracketPairs, numOfOpenBrackets + 1, numOfCloseBrackets);
        }
    }
}

int main()
{
    int n = 0;
    do
    {
        n = input<int>("Enter a positive integer: ");
    } while (n <= 0);

    printBrackets("", n, 0, 0);

    return 0;
}

/*
******s-iMac:Assignment code ******$ ./out
Enter a positive integer: 4
()()()()
()()(())
()(())()
()(()())
()((()))
(())()()
(())(())
(()())()
(()()())
(()(()))
((()))()
((())())
((()()))
(((())))
******s-iMac:Assignment code ******$ ./out
Enter a positive integer: 2
()()
(())
******s-iMac:Assignment code ******$ ./out
Enter a positive integer: 1    
()
*/