#include <iostream>
#include "nmlh_alloc.hpp"


using namespace std;

int main(){
    
    nmlh::allocator gen;

    int* x1 = new int[10];
    int* x2 = gen.alloc<int>(100);

    cout << x2 << endl;

    gen.free(x2);

    int* x3 = gen.alloc<int>(5);

    
    cout << x3 << endl;
    

    int* x4 = gen.alloc<int>(20);

    cout << x4 << endl;
    gen.free(x3);
    gen.free(x4);

    delete[] x1;

    size_t x;
    cin >> x;
    cout << nmlh::align(x) << endl;
    cout << getpagesize() << endl;
    return 0;
}