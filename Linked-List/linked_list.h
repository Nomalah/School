/*
Created & Written by Dallas Hart
Copyright April 17 2020

This is the header file for my linked list library
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory> 
#include <cstddef>
#include <cstdlib>
#include <list>
#include <initializer_list>

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
        linked_list(std::initializer_list<int> list_initializer);
        ~linked_list();

        // Push & Pop functions
        void push(int value);
        int pop();

        // Insert & Remove functions
        void insert(int index, int value);
        void remove(int index);

        // Index function
        int& operator[](int index);
};

template<class T, class Allocator = std::allocator<T>>
class d_linked_list{
    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef Allocator::pointer pointer;
        typedef Allocator::const_pointer const_pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;

        void push_front(const T& val);
        void push_front(T&& val);
        void push_back(const T& val);
        void push_back(T&& val);

        void pop_front() noexcept;
        void pop_back() noexcept;

    private:
        template<class T>
        struct link{
            link<T>* previous;
            T data;
            link<T>* next;
        }

};

#endif // LINKED_LIST_H