#include <iostream>
#include <math.h>
#include "timer.h"

#define TEST_CASES 100

using namespace std;


int main(){
    timer clock;

    double total = 0;
    long long total_tests = 0;
    for (int i = 0; i < TEST_CASES; i++){
        clock.reset();

        long long n_size = 10;

        for (long long n1 = 1; n1 < n_size; n1++){
            long double n2 = sqrt(n1 * n_size - n1 + 0.25) /*-n1*/ + 0.5;
            if ((int)n2 == n2)
                cout << n1 * (n_size - 1) + (int)n2 << "\n";
        }

        for (int n_len = 4; n_len <= 16; n_len += 2){
            n_size *= 10;

            int inc = 0;

            for (long long n1 = n_size / 10; n1 < n_size; n1 += (inc++ == 2 ? (inc = 0, 2) : 4)){
                long double n2 = sqrt(n1 * n_size - n1 + 0.25) /*-n1*/ + 0.5;
                if (n2 == (int)n2)
                    cout << n1 * (n_size - 1) + (int)n2 << "\n";
            }
        }
        clock.stop();
        total += clock.get();
    }
    cout << "Total run time: " << total << "s" << endl;
    cout << "Average run time per case: " << total / TEST_CASES << "s" << endl;
    return 0;
}
