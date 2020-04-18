/*
Created & Written by Dallas Hart
Copyright April 17 2020

This is the implementation of the outline in linked_list.h
*/

#include "linked_list.h"

linked_list::linked_list(){
    length = 0;
    first_link = {nullptr, 0, nullptr};
    last_link = &first_link;
}

void linked_list::push(int value){
    last_link->next_link = new link();
    *(last_link->next_link) = {last_link, value, nullptr};
    last_link = last_link->next_link;
    length++;
}

int linked_list::pop(){
    if(length == 0) return 0;
    link* current_link = last_link->previous_link;
    int temp = last_link->value;
    delete current_link->next_link;
    current_link->next_link = nullptr;
    last_link = current_link;
    length--;
    return temp;
}

int linked_list::operator[](int index){
    if (index + 1 > length || index < 0) return 0;

    link* current_link = &first_link;
    for(int i = 0; i <= index; i++){
        current_link = current_link->next_link;
    }
    return current_link->value;
}