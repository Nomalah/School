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
        int total = inputSequence[i];
        for (std::size_t j = i + 1; j < inputSequence.size(); j++) {
            total += inputSequence[j];
            // Subsequence sum is a prime
            if(isPrime[total]){
                std::cout << inputSequence[i];
                for (std::size_t c = i + 1; c <= j; c++) {
                    std::cout << " + " << inputSequence[c];
                }
                std::cout << " = " << total << std::endl;
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
*/