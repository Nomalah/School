/*
Created & Written by Dallas Hart
Copyright April 17 2020

This is the header file for my linked list library
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct link{
    link* previous_link;
    int value;
    link* next_link;
};

class linked_list{
    public:
        int length;
        link first_link;
        link* last_link;
        linked_list();
        //~linked_list();

        void push(int value);
        int pop();

        int operator[](int index);
};

#endif // LINKED_LIST_H