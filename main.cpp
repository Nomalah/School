#include <iostream>

//#define NMLH_DEBUG 1
#include <chrono>
#include "nmlh_dynamic_alloc.hpp"

using namespace std;

class test{
    public:
        int x;
        int y;

        test(){
            cout << "test constructor" << endl;
        }

        ~test(){
            cout << "test destructor" << endl;
        }
};

int main(){
    
    nmlh::allocator gen;

    test* y1 = gen.alloc<test>(3);
    cout << y1 << endl;
    gen.dealloc(y1);

    cin.get();
    return 0;
}