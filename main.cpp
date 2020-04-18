/*
Created & Written by Dallas Hart
Copyright April 17 2020

This is the example file for my linked list library
*/

#include <iostream>
#include "linked_list.h"

using namespace std;

int main(){
    linked_list test;
    for (int i = 0; i < 1000000; i++){
        test.push(i);
    }
    //test.push(15);
    cout << test.pop() << endl;
    cout << test.pop() << endl;
    cout << test.pop() << endl;
    cout << test[500] << endl;
    return 0;
}