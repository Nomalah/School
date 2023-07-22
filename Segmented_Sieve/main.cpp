#include <iostream>

#define MAX_SEARCH 1500000000

using namespace std;

bool is_prime(int to_test);

int main(){
    /*bool hello;
    for(int i = 0; i < MAX_SEARCH; i++){
        hello = is_prime(i);
    }

    if(hello){
        cout<<"hi";
    }*/

    bool* sieve = new bool[MAX_SEARCH]; 
    for(int i = 0; i < MAX_SEARCH; i++){
        sieve[i] = true;
    }

    for(int i = 2; i*i < MAX_SEARCH; i++){
        if(sieve[i])
            for(int j = i + i; j < MAX_SEARCH; j += i)
                sieve[i] = false;

        if((i & 8191) == 0)
            cout << i << '\r';
    }


    /*for(int i = 2; i < MAX_SEARCH; i++){
        if(sieve[i]){
            cout << i << '\r';
        }
    }*/

    return 0;
}
// space complex O(n)
// O(n * log(log(n)))

// O(n^2)

// space complex O(1)
bool is_prime(int to_test){
    for(int i = 2; i < to_test; i++)
        if(to_test % i == 0)
            return false;
    
    return true;
}