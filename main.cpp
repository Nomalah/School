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

        long long n_size = 1;
        for (int n_len = 2; n_len <= 16; n_len += 2){
            n_size *= 10;
            long long n_max = n_size - 1;

            cout << "n_len  - " << n_len << endl;
            cout << "n_max  - " << n_max << endl;

            int incrementer = n_len == 2 ? 0 : -1;

            for (long long n1 = n_len == 2 ? 4 : n_size / 10; n1 < n_max; n1 += incrementer == 2 ? 2 : 4){
                long double n2 = sqrt(n1 * n_max + 0.25) + 0.5;
                if ((int)n2 == n2)
                    cout << n1 * n_max + (int)n2 << "\n";
                incrementer += incrementer == 2 ? -2 : 1;
            }
        }
        clock.stop();
        total += clock.get();
        //clock.print();
    }
    cout << "Total run time: " << total << "s" << endl;
    cout << "Average run time per case: " << total / TEST_CASES << "s" << endl;
    return 0;
}
