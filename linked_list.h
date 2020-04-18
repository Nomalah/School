/*
Created & Written by Dallas Hart
Copyright April 17 2020

This is the header file for my linked list library
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// The linked list is built up of links (24 byte size, 1/3 the storage efficency of a normal array)
struct link{
    // Stores the previous link in the chain
    link* previous_link;

    // Stores the actual value
    int value;

    // Stores the next link in the chain
    link* next_link;
};

// The linked list class
class linked_list{
    public:
        // The list has a length
        int length;

        // Starting link
        link* first_link;

        // End link
        link* last_link;

        // List constructor & destructor
        linked_list();
        ~linked_list();

        // Push & Pop functions
        void push(int value);
        int pop();

        // Insert & Remove functions
        void insert(int index, int value);
        void remove(int index);

        // Index function
        int operator[](int index);
};

#endif // LINKED_LIST_H