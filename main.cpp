/*
Created & Written by Dallas Hart
Copyright April 17 2020

This is the example file for my linked list library
*/

#include <iostream>
#include "linked_list.h"

using namespace std;

int main(){
    linked_list test {10, 20, 50, 2, 3};
    cout << test[2] << endl;
    cout << test.pop() << endl;

    for (int i = 0; i < 5; i++)
        test.push(i);
    
    test.push(15);
    
    cout << test.pop() << endl;
    cout << test[0] << endl;
    cout << test.pop() << endl;

    test.insert(5, 20);
    cout << test[5] << endl;
    test.remove(5);
    cout << test[5] << endl;


    return 0;
}