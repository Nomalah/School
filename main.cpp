#include <iostream>

//#define NMLH_DEBUG 1

#include "nmlh_dynamic_alloc.hpp"

using namespace std;

class test{
    public:
        test(){
            cout << "test constructor" << endl;
        }

        ~test(){
            cout << "test destructor" << endl;
        }
};

int main(){
    
    nmlh::allocator gen;

    int* x2 = gen.alloc<int>(99);

    cout << x2 << endl;

    test* y1 = gen.alloc<test>(3);
    cout << y1 << endl;

    //gen.free(x2);

    int* x3 = gen.alloc<int>(5);

    
    cout << x3 << endl;
    

    int* x4 = gen.alloc<int>(20);

    cout << x4 << endl;
    //gen.free(x3);
    //gen.free(x4);

    size_t x;
    cin >> x;
    cout << nmlh::align(x) << endl;
    cout << getpagesize() << endl;
    return 0;
}