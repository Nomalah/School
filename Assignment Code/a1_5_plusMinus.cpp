// a1_5_plusMinus
// Dallas Hart
//
// Takes in n and m, outputs solutions for 1 +/- 2 +/- 3 +/- 4 +/- ... +/- n = m

#include <iostream>
#include <numeric>

#include "NMLH_error_checking.hpp"

bool evaluate(uint32_t size, uint32_t toEvaluate, int target, int max) { 
    // Use bits of toEvaluate as a permutations for the +/- signs
    int total = 0;
    for (int i = 1; i <= max; i++) {
        if (size & toEvaluate)
            total -= i;
        else
            total += i;
        size >>= 1;
    }
    return target == total;
}

// Print solution (assumes inputs to be true)
void visualize(uint32_t size, uint32_t toEvaluate, int target, int max) {
    for (int i = 1; i <= max; i++) {
        if (size & toEvaluate) {
            std::cout << "- " << i << " ";
        } else {
            std::cout << "+ " << i << " ";
        }
        size >>= 1;
    }
    std::cout << "= " << target << std::endl;
}

int main() {
    // Input & Error detection
    int n, m;
    std::cout << "Please enter two numbers, n and m." << std::endl;
    do {
        n = input<int>("Enter n (1 <= n <= 20): ");
    } while (!(n > 0 && n < 21));
    do {
        m = input<int>("Enter m (-20 <= m <= 20): ");
    } while (!(m > -21 && m < 21));


    // Compute solutions
    int solutions = 0;
    uint32_t size = 1 << (n - 1); // Will give us the needed 2^(n-1) combinations
    for (uint32_t i = size - 1;; i--){ 
        if(evaluate(size, i, m, n)){
            visualize(size, i, m, n);
            solutions++;
        }
        if (i == 0) break; // unsigned ints will overflow when subtracted
    }
    std::cout << solutions << " solution(s)" << std::endl;
}

/*
******s-iMac:assignment code ******$ ./out
Please enter two numbers, n and m.
Enter n (1 <= n <= 20): 5
Enter m (-20 <= m <= 20): 4
0 solution(s)
******s-iMac:assignment code ******$ ./out
Please enter two numbers, n and m.
Enter n (1 <= n <= 20): 5
Enter m (-20 <= m <= 20): 7
+ 1 + 2 + 3 - 4 
*/