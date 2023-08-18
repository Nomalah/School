// a1_6_primeSubsequence
// Dallas Hart
//
// Finds subsequences where the sum equals a prime number

#include <iostream>
#include <vector>

#include "NMLH_error_checking.hpp"
#define IN_ARR_SIZE_MAX 1000
#define IN_VAL_SIZE_MAX 1000

int main() {
    // Input handling
    std::size_t inputSequenceSize = 0;
    do {
        inputSequenceSize = input<std::size_t>("Enter the size of the initial sequence: ");
    } while (inputSequenceSize <= 0 || inputSequenceSize > IN_ARR_SIZE_MAX);

    std::vector<std::size_t> inputSequence;

    std::size_t fullSequenceSum = 0;
    for (std::size_t i = 0; i < inputSequenceSize; i++) {
        std::size_t toInput;
        do {
            toInput = input<std::size_t>("Enter Value #" + std::to_string(i+1) + ": ");
        } while (toInput <= 0 || toInput > IN_VAL_SIZE_MAX);
        inputSequence.push_back(toInput);
        fullSequenceSum += toInput;
    }

    // Sieve of Eratosthenes
    bool isPrime[fullSequenceSum + 1];  // Add 1 so [fullSequenceSum] is accessable
    for (std::size_t i = 0; i <= fullSequenceSum; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = false;
    isPrime[1] = false;

    for (std::size_t p = 2; p * p <= fullSequenceSum; p++) {
        for (std::size_t m = p + p; m <= fullSequenceSum; m += p) {
            isPrime[m] = false;
        }
    }


    // Subsequence sums
    for (std::size_t i = 0; i < inputSequence.size(); i++) {
        int subsequenceSum = inputSequence[i];
        for (std::size_t j = i + 1; j < inputSequence.size(); j++) {
            subsequenceSum += inputSequence[j];
            // Subsequence sum is a prime
            if(isPrime[subsequenceSum]){
                std::cout << inputSequence[i];
                for (std::size_t c = i + 1; c <= j; c++) {
                    std::cout << " + " << inputSequence[c];
                }
                std::cout << " = " << subsequenceSum << std::endl;
            }
        }
    }
    return 0;
}

/*
******s-iMac:assignment code ******$ ./out
Enter the size of the initial sequence: 5
Enter Value #1: 1
Enter Value #2: 2
Enter Value #3: 3
Enter Value #4: 4
Enter Value #5: 5
1 + 2 = 3
2 + 3 = 5
3 + 4 = 7
******s-iMac:assignment code ******$ ./out
Enter the size of the initial sequence: 9
Enter Value #1: 1
Enter Value #2: 5
Enter Value #3: 8
Enter Value #4: 2
Enter Value #5: 4
Enter Value #6: 0
Enter Value #6: -1
Enter Value #6: -29
Enter Value #6: 6
Enter Value #7: 35
Enter Value #8: 29
Enter Value #9: 1067
Enter Value #9: 167
1 + 5 + 8 + 2 + 4 + 6 + 35 = 61
1 + 5 + 8 + 2 + 4 + 6 + 35 + 29 + 167 = 257
5 + 8 = 13
5 + 8 + 2 + 4 = 19
5 + 8 + 2 + 4 + 6 + 35 + 29 = 89
8 + 2 + 4 + 6 + 35 + 29 + 167 = 251
2 + 4 + 6 + 35 = 47
4 + 6 + 35 + 29 + 167 = 241
6 + 35 = 41
Marians-iMac:assignment code marian$ ./out
Enter the size of the initial sequence: 20
Enter Value #1: 517
Enter Value #2: 789
Enter Value #3: 9
Enter Value #4: 970
Enter Value #5: 437
Enter Value #6: 826
Enter Value #7: 635
Enter Value #8: 191
Enter Value #9: 304
Enter Value #10: 207
Enter Value #11: 603
Enter Value #12: 233
Enter Value #13: 258
Enter Value #14: 793
Enter Value #15: 509
Enter Value #16: 100
Enter Value #17: 680
Enter Value #18: 194
Enter Value #19: 439
Enter Value #20: 671
9 + 970 + 437 + 826 + 635 + 191 + 304 + 207 + 603 + 233 + 258 = 4673
9 + 970 + 437 + 826 + 635 + 191 + 304 + 207 + 603 + 233 + 258 + 793 + 509 + 100 + 680 + 194 = 6949
9 + 970 + 437 + 826 + 635 + 191 + 304 + 207 + 603 + 233 + 258 + 793 + 509 + 100 + 680 + 194 + 439 + 671 = 8059
437 + 826 + 635 + 191 = 2089
437 + 826 + 635 + 191 + 304 = 2393
437 + 826 + 635 + 191 + 304 + 207 + 603 = 3203
826 + 635 + 191 + 304 + 207 + 603 + 233 = 2999
826 + 635 + 191 + 304 + 207 + 603 + 233 + 258 = 3257
635 + 191 + 304 + 207 + 603 + 233 + 258 + 793 + 509 = 3733
635 + 191 + 304 + 207 + 603 + 233 + 258 + 793 + 509 + 100 = 3833
635 + 191 + 304 + 207 + 603 + 233 + 258 + 793 + 509 + 100 + 680 = 4513
304 + 207 + 603 + 233 + 258 + 793 + 509 + 100 + 680 + 194 = 3881
207 + 603 + 233 + 258 = 1301
233 + 258 = 491
233 + 258 + 793 + 509 + 100 + 680 + 194 = 2767
233 + 258 + 793 + 509 + 100 + 680 + 194 + 439 + 671 = 3877
258 + 793 = 1051
509 + 100 + 680 = 1289
509 + 100 + 680 + 194 = 1483
509 + 100 + 680 + 194 + 439 + 671 = 2593
*/