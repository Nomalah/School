/*
Created & Written by Dallas Hart
Copyright April 17 2020

This is the implementation of the outline in linked_list.h
*/

#include <initializer_list>
#include "linked_list.h"

// Linked list constructor
linked_list::linked_list(){
    // When a list starts it has no length
    length = 0;

    // The first link is like a placeholder, has none before, none after, and no value
    first_link = new link();
    *first_link = {nullptr, 0, nullptr};

    // At the start of list, the first link is the same last
    last_link = first_link;
}

// Linked list initializer_list constructor
linked_list::linked_list(std::initializer_list<int> list_initializer){
    // When a list starts it has no length
    length = 0;

    // The first link is like a placeholder, has none before, none after, and no value
    first_link = new link();
    *first_link = {nullptr, 0, nullptr};

    // At the start of list, the first link is the same last
    last_link = first_link;

    for(int i : list_initializer)
        push(i);
}

// Linked list destructor
linked_list::~linked_list(){
    // Start at the second last link
    link* current_link = last_link->previous_link;

    // Loop through the chain from back to front
    for(int i = 0; i < length; i++){
        // Delete the link ahead of the current link
        delete current_link->next_link;

        // Set the current link to the previous link
        current_link = current_link->previous_link;
    }
    // Delete the first link in the chain
    delete first_link;
}

// Linked list push function
// Takes in a value to push to the end of the list
void linked_list::push(int value){
    // Add a link to the end of the list
    last_link->next_link = new link();

    // Initialize the new link with the pushed value
    *(last_link->next_link) = {last_link, value, nullptr};

    // Push forward the last link
    last_link = last_link->next_link;

    // Increase the length of the list
    length++;
}

// Linked list pop function
// Returns the last value of the list and deletes it from the list
int linked_list::pop(){
    // If there are no items in the list, it cannot pop anything off of the list
    if(length == 0) return 0;

    // Store the value of the last link in the list
    int temp = last_link->value;

    // Store the second last link 
    link* current_link = last_link->previous_link;

    // Delete the last link
    delete current_link->next_link;

    // Make the second last link the last link
    current_link->next_link = nullptr;
    last_link = current_link;

    // Shrink the list size
    length--;

    // Return the value of the pop'd value 
    return temp;
}

// Linked list insert function
// Inserts a link at a specified index in the list
void linked_list::insert(int index, int value){
    // If the index is greater then the length or the index is smaller then 0, the index is out of bounds
    if (index + 1 > length || index < 0) return;

    // Start the iteration at the first link
    link* current_link = first_link;

    // Iterate through the list through to the index
    for(int i = 0; i < index; i++) current_link = current_link->next_link;

    // Store the link before and after the current link
    link* temp_next_link = current_link->next_link;
    
    // Create the new link
    current_link->next_link = new link();
    *(current_link->next_link) = {current_link, value, temp_next_link};
}

// Linked list remove function
// Removes a link at a specified index from the list
void linked_list::remove(int index){
    // If the index is greater then the length or the index is smaller then 0, the index is out of bounds
    if (index + 1 > length || index < 0) return;

    // Start the iteration at the first link
    link* current_link = first_link;

    // Iterate through the list through to the index
    for(int i = 0; i <= index; i++) current_link = current_link->next_link;

    // Store the link before and after the current link
    link* temp_previous_link = current_link->previous_link;
    link* temp_next_link = current_link->next_link;
    
    // Delete the current link
    delete current_link;

    // Reconnect the now disconnected links
    temp_previous_link->next_link = temp_next_link;
    temp_next_link->previous_link = temp_previous_link;
}

// Linked list index function
// Returns the value of the index specified
int linked_list::operator[](int index){
    // If the index is greater then the length or the index is smaller then 0, the index is out of bounds
    if (index + 1 > length || index < 0) return 0;

    // Start the iteration at the first link
    link* current_link = first_link;

    // Iterate through the list through to the index
    for(int i = 0; i <= index; i++) current_link = current_link->next_link;

    // Return the index value
    return current_link->value;
}