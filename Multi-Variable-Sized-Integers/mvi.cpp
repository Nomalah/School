#include <iostream>
#include <string>

#include "mvi.h"

int operation_size = 0;

#define STEP for(int step = 0; step < operation_size; step++) std::cout << "    "

#define LOG(x, y, a, b) STEP; std::cout << x << " " << y << " " << a << " " << b << std::endl

unsigned char from_hex(const char hex_character){
    switch (hex_character){
        case '0' ... '9':
            return hex_character - '0';
        case 'A' ... 'F':
            return hex_character - 'A' + 10;
        case 'a' ... 'f':
            return hex_character - 'a' + 10;
        default:
            return 0;
    }
}

char to_hex(const unsigned char int_character){
    switch (int_character){
        case 0 ... 9:
            return int_character + '0';
        case 10 ... 15:
            return int_character + 'A' - 10;
        default:
            return '*';
    }
}

std::string to_hex(const mvi& integer){
    std::string result = "0x";
    //std::cout << integer.num_of_bytes << std::endl;
    for (int i = 0; i < integer.num_of_bytes; i++){
        //LOG()
        //std::cout << to_hex(integer.data[i] >> 4) + to_hex(integer.data[i] & 15) << std::endl;
        result += to_hex(integer.data[i] >> 4);
        result += to_hex(integer.data[i] & 15);
    }
    return result;
}

void mvi::print(){
    std::cout << "0x";
    for (int i = 0; i < num_of_bytes; i++)
        std::cout << to_hex(data[i] >> 4) << to_hex(data[i] & 15);
    std::cout << std::endl;
}

mvi::mvi(int init_num_of_bytes, std::string initializer) : num_of_bytes(init_num_of_bytes){
    // Allocate enough memory for the number of bytes requested
    data = new unsigned char[num_of_bytes];

    if (num_of_bytes * 2 != initializer.length()){
        std::cout << "Invalid initializer length" << std::endl;
    }else if (initializer == ""){
        for (int i = 0; i < num_of_bytes; i++)
            data[i] = 0;
    }else{
        for (int i = 0; i < num_of_bytes; i++)
            data[i] = from_hex(initializer[2 * i]) << 4 | from_hex(initializer[2 * i + 1]);
    }
    LOG("C", "Init", "0x" + initializer + " =>", to_hex(*this));
}

mvi::mvi(int init_num_of_bytes, unsigned int initializer) : num_of_bytes(init_num_of_bytes){
    // Allocate enough memory for the number of bytes requested
    data = new unsigned char[num_of_bytes];

    for (int i = 0; i < num_of_bytes-4; i++)
        data[i] = 0;

    for (int i = num_of_bytes-4 > 0 ? num_of_bytes-4 : 0; i < num_of_bytes; i++)
        data[i] = initializer >> (num_of_bytes-1-i)*8;

    LOG("C", "Int Init", initializer, "=> " + to_hex(*this));
}

mvi mvi::operator+(const mvi &mvi_add_rhs){
    LOG("Add", "", to_hex(*this) + " + " + to_hex(mvi_add_rhs), "{");
    operation_size++;

    if (num_of_bytes != mvi_add_rhs.num_of_bytes){
        std::cout << "Incompatable integer lengths" << std::endl;
        mvi temp(*this);
        return temp;
    }
    unsigned char current_carry = 0;

    mvi result(*this);
    for (int i = num_of_bytes - 1; i >= 0; i--){
        result.data[i] += mvi_add_rhs.data[i] + current_carry;
        current_carry = result.data[i] < (data[i] > mvi_add_rhs.data[i] ? data[i] : mvi_add_rhs.data[i]) + current_carry ? 1 : 0;
    }

    operation_size--;
    LOG("}", "Add R ->", to_hex(result), "");
    return result;
}

mvi operator~(const mvi& mvi_neg_rhs){
    LOG("Negate", "", "~"+to_hex(mvi_neg_rhs), "{");
    operation_size++;

    mvi result (mvi_neg_rhs);
    for (int i = mvi_neg_rhs.num_of_bytes - 1; i >= 0; i--)
        result.data[i] = ~result.data[i];
    
    operation_size--;
    LOG("}", "Negate R ->", to_hex(result), "");
    return result;
}

mvi mvi::operator-(const mvi& mvi_sub_rhs){
    LOG("Sub", "", to_hex(*this) + " - " + to_hex(mvi_sub_rhs), "{");
    operation_size++;

    mvi result(this->num_of_bytes, 1);
    result = *this + ~mvi_sub_rhs + result;
    
    operation_size--;
    LOG("}", "Sub R ->", to_hex(result), "");
    return result;
}

// Underlying copy, move and destructor operators

mvi::mvi() : num_of_bytes(-1){
    LOG("C", "Blank", "", "");
    // Allocate enough memory for the number of bytes requested
    data = nullptr;
}

mvi::mvi(const mvi &mvi_copy_src) : num_of_bytes(mvi_copy_src.num_of_bytes){
    LOG("C Copy", "", to_hex(mvi_copy_src), "");
    data = new unsigned char[num_of_bytes];
    for (int i = 0; i < num_of_bytes; i++)
        data[i] = mvi_copy_src.data[i];
}

mvi::mvi(mvi &&mvi_move_src) : num_of_bytes(mvi_move_src.num_of_bytes), data(mvi_move_src.data){
    LOG("C Move", "", to_hex(mvi_move_src), "");
    mvi_move_src.num_of_bytes = 0;
    mvi_move_src.data = nullptr;
}

mvi& mvi::operator=(const mvi &mvi_copy_rhs){
    LOG("A Copy", to_hex(mvi_copy_rhs) + " ->", to_hex(*this), "");
    if (this != &mvi_copy_rhs){
        num_of_bytes = mvi_copy_rhs.num_of_bytes;

        delete[] data;
        data = new unsigned char[num_of_bytes];
        for (int i = 0; i < num_of_bytes; i++)
            data[i] = mvi_copy_rhs.data[i];
    }
    return *this;
}

mvi& mvi::operator=(mvi&& mvi_move_rhs){
    LOG("A Move", to_hex(mvi_move_rhs) + " ->", to_hex(*this), "");
    if (this != &mvi_move_rhs){
        num_of_bytes = mvi_move_rhs.num_of_bytes;
        mvi_move_rhs.num_of_bytes = 0;

        delete[] data;
        data = mvi_move_rhs.data;
        mvi_move_rhs.data = nullptr;
    }
    return *this;
}

mvi::~mvi(){
    //if(num_of_bytes > 0)
        //LOG("Destroy:", "", to_hex(*this), "{}");
    num_of_bytes = 0;
    delete[] data;
}
