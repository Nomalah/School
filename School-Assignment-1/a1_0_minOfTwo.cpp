// a1_0_minOfTwo
// Dallas Hart
//
// This program will print the minimum of two user inputted integers.

#include <iostream>
#include "NMLH_error_checking.hpp"

int main() {
    int a, b;
    std::cout << "Please enter two numbers." << std::endl;
    a = input<int>("Number one: ");
    b = input<int>("Number two: ");
    std::cout << "The minimum of both numbers is " << (a < b ? a : b) << std::endl;
    return 0;
}

/*
******s-iMac:Assignment Code ******$ ./a1_1_minOfTwo
Please enter two numbers¬
Number one: 2
Number two: 2
The minimum of both numbers is 2
******s-iMac:Assignment Code ******$ ./a1_1_minOfTwo
Please enter two numbers.
Number one: -1
Number two: -5g
The minimum of both numbers is -5
******s-iMac:Assignment Code ******$ ./a1_1_minOfTwo
Please enter two numbers.
Number one: bruh25
Number one: hel-5lo
Number one: 6
Number two: -3
The minimum of both numbers is -3
*/