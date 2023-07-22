/*
May 6 2020 Lesson/Tutorial
Dynamic / Heap allocated arrays
*/

#include <iostream>

using namespace std;

// Structs are a grouping together of multiple variables into one type
struct custom_struct{ // Structs will pad to the next multiple of 16 bytes
    int x, y; // 4 bytes * 2
    float q, p; // 4 bytes * 2
    double d; // 8 bytes
    long double ld; // 16 bytes (actually 10 but extends to 16)
    char a[13]; // 1 byte * 14
    // 8 bytes + 8 bytes + 8 bytes + 16 bytes + 13 bytes = 53 bytes
};  // 53 bytes (padding is 11 bytes) up to 64 bytes

int main(){
    // ===================Type-Sizes====================
    // sizeof() returns the number of bytes of the specified type
    cout << "bool size in bytes: " << sizeof(bool) << endl; // bool is 1 byte
    cout << "char size in bytes: " << sizeof(char) << endl; // char is 1 byte
    cout << "int size in bytes: " << sizeof(int) << endl; // int is 4-bytes
    cout << "long size in bytes: " << sizeof(long) << endl; // long is either 4 bytes or 8 bytes
    cout << "long long size in bytes: " << sizeof(long long) << endl; // long long is 8-bytes
    cout << "float size in bytes: " << sizeof(float) << endl; // float is 4-bytes
    cout << "double size in bytes: " << sizeof(double) << endl; // double is a 8-byte type
    cout << "long double size in bytes: " << sizeof(long double) << endl; // long double is generally a 10-byte type (extended to 16)
    cout << "custom_struct size in bytes: " << sizeof(custom_struct) << endl; // cool_struct is a 64-byte type (even thought it only takes up 51)
    // =================================================

    // ================Stack Allocation=================
    // The stack is an area in memory that is generally faster then the heap, 
    // BUT, it has a soft limit of 2,097,152 bytes (stack soft max) VS the heap
    // which has the limit of your installed ram plus your paging system in your OS

    // This is about the max size of array you should use if you want an array in the stack
    // it is very close to the limit, if you choose to go above this limit, change your compiler
    // options so that you can go above the 2 MB soft limit safely.
    int normal_arr[500000]; // 500,000 * 4 = 2,000,000 vs 2,097,152(stack soft max)

    // Initalize the array so that the value of any given position is equal to it's index
    for (int i = 0; i < 500000; i++)
        normal_arr[i] = i;

    // Print out the array on the same line
    for (int i = 0; i < 500000; i++)
        cout << normal_arr[i] << '\r';
    cout << endl;
    // =================================================
    
    // =====================Pointers====================
    int var_a = 5;
    // The location in memory in which var_a is stored
    cout << "Address of variable var_a: " << &var_a << endl;
    cout << "Value of variable var_a: " << var_a << endl;
    
    // A pointer is address, and when you derefrence it, 
    // you follow that pointer to another memory location
    int* ptr_a = &var_a; // ptr_a = address of var_a
    cout << "Address of ptr_a: " << &ptr_a << endl;
    cout << "Value of ptr_a: " << ptr_a << endl;
    cout << "ptr_a points to: " << *ptr_a << endl;

    // We can alter the original variable, from the pointer of it
    *ptr_a = 20; // Now var_a = 20
    
    cout << "==== Set *ptr_a to 20 ===="<< endl;
    cout << "Value of ptr_a: " << ptr_a << endl;
    cout << "ptr_a points to: " << *ptr_a << endl;
    cout << "Value of variable var_a: " << var_a << endl;
    // =================================================

    // =================Heap-Allocation=================
    // Allocate 400 megabytes of integers
    long long *arr_of_int = new long long[52428800]; // 8 bytes * 52428800 / 1024 / 1024 = 200 megabytes
    
    // Initialize the array to 0
    for (int i = 0; i < 52428800; i++)
        arr_of_int[i] = 0;

    custom_struct *arr_of_structs = nullptr;
    for(int i = 0; i < 1024; i++){
    // Allocate 1 kilobyte of custom structs
        delete[] arr_of_structs;
        arr_of_structs = new custom_struct[16384]; // 1024 bytes / 1 kilobyte (64 bytes * 16)
    }
    // Print the address of each of the array's members
    for (int i = 0; i < 16; i++){
        // Notice that the address' are spread apart by 64 (4 in the second column from the right)
        cout << "address of arr_of_structs[" << i << "]: " << arr_of_structs + i << endl;
    }
    // =================================================

    // Wait before ending the program
    cin.get();

    // DO THIS, DO NOT FORGET THIS OR ELSE YOU WILL MEMORY LEAK
    // Free the array's memory
    delete[] arr_of_structs;
    delete[] arr_of_int;

    // End the program
    return 0;
}