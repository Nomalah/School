#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include "timer.h"

using namespace std;

int main(){
    timer clock;
    clock.start();
    u_int32_t max_search_number = 0x0FFFFFFF;
    //u_int32_t max_search_number = 0x00100000;
    int* factors;
    for (u_int32_t i = 0; i < max_search_number; i++)
        is_prime[i] = true;
    clock.stop();
    clock.print();
    clock.reset();
    for (u_int64_t i = 2; i < sqrt(max_search_number); i++)
        if (is_prime[i])
            for (u_int64_t z = i * i; z < max_search_number; z += i)
                is_prime[z] = false;
    clock.stop();
    clock.print();
    clock.reset();
    ofstream file;
    file.open("primes.bin", ios::out | ios::binary);
    for (u_int32_t i = 2; i <= max_search_number; i++)
        if (is_prime[i])
            file << i;
    file.close();
    clock.print();
}