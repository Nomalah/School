#include <iostream>

#include "mvi.h"

using namespace std;

int main(){
    //cout << from_hex('C');
    mvi var1 (4, 20);
    //var1.print();
    mvi var2 (4, 10);
    //var2.print();
    mvi var3 (4, 5);

    mvi result;

    result = var1+var2-var3;
    //result = result - var3;

    result.print();
    //int p = 5;

    return 0;
}