// a1_1_standardForm
// Dallas Hart
//
// Takes in two 2D points and outputs the equation for the line connecting the two in standard form.

#include <iostream>
#include <numeric>

#include "NMLH_error_checking.hpp"

int main() {
    // Take inputs for 2D points
    int xP1, yP1, xP2, yP2;
    std::cout << "Please enter two 2D points." << std::endl;
    xP1 = input<int>("Enter point 1's x component: ");
    yP1 = input<int>("Enter point 1's y component: ");
    xP2 = input<int>("Enter point 2's x component: ");
    yP2 = input<int>("Enter point 2's y component: ");

    // Calcuation for standard form
    int a = yP2 - yP1;
    int b = xP1 - xP2;
    int c = yP1 * xP2 - yP2 * xP1;

    // A must be positive
    if (a < 0) {
        a = -a;
        b = -b;
        c = -c;
    }

    // Simplify Equation
    int gcd_equation = std::gcd(a, std::gcd(b, c));
    a /= gcd_equation;
    b /= gcd_equation;
    c /= gcd_equation;
    

    // Magic formatting
    bool aExists = a != 0;
    bool bExists = b != 0;
    bool cExists = c != 0;

    // Formatting for AX
    if (aExists) {
        if(a != 1){
            std::cout << a;
        }
        std::cout << "x";

        if (bExists) {
            std::cout << (b < 0 ? " - " : " + ");
        } else if (cExists) {
            std::cout << (c < 0 ? " - " : " + ");
        }
    }

    // Formatting for BY
    if (bExists) {
        if (b == -1 && !aExists) {
            std::cout << "-y";
        } else if (b == 1){
            std::cout << "y";
        } else {
            std::cout << (aExists ? std::abs(b) : b) << "y"; // Leading - if a does not exist
        }
        
        if (cExists) {
            std::cout << (c < 0 ? " - " : " + ");
        }
    }

    // Formatting for C
    if (cExists) {
        std::cout << std::abs(c);  // c will always exist with something else
    }
    std::cout << " = 0" << std::endl;
}

/*
******s-iMac:assignment code ******$ ./out
Please enter two 2D points.
Enter point 1's x component: 0 
Enter point 1's y component: 2
Enter point 2's x component: 2
Enter point 2's y component: 2
-y + 2 = 0
******s-iMac:assignment code ******$ ./out
Please enter two 2D points.
Enter point 1's x component: 0
Enter point 1's y component: 2
Enter point 2's x component: 2
Enter point 2's y component: -8
5x + y - 2 = 0
******s-iMac:Assignment Code ******$ ./out
Please enter two 2D points.
Enter point 1's x component: 2
Enter point 1's y component: 0
Enter point 2's x component: 2
Enter point 2's y component: 2
x - 2 = 0
*/