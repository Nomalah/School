#include <functional>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "matrix.h"

//#define INDEX(x, y) (x + y * initial_columns)
//unsigned num_of_columns;
//unsigned num_of_rows;
//unsigned long long size;
//double* data; // Data is stored linearly (x + y * num_of_columns)

// Normal constructor
matrix::matrix(unsigned initial_columns, unsigned initial_rows)
    : num_of_columns(initial_columns), num_of_rows(initial_rows), size(initial_columns * initial_rows){
    data = new double[size];
}

// Copy constructor
matrix::matrix(const matrix& copy_src)
    : num_of_columns(copy_src.num_of_columns), num_of_rows(copy_src.num_of_rows), size(copy_src.size){
    data = new double[size];
    for(unsigned long long index = 0; index < size; index++)
        data[index] = copy_src.data[index];
}

// Move constructor
matrix::matrix(matrix&& move_src)
    : num_of_columns(move_src.num_of_columns), num_of_rows(move_src.num_of_rows), size(move_src.size), data(move_src.data){
    move_src.data = nullptr;
}

// Copy assignment operator
matrix& matrix::operator=(const matrix& copy_rhs){
    if(this != &copy_rhs){
        delete[] data;
        num_of_columns = copy_rhs.num_of_columns;
        num_of_rows = copy_rhs.num_of_rows;
        size = copy_rhs.size; 
        data = copy_rhs.data;

        data = new double[size];
        for(unsigned long long index = 0; index < size; index++)
            data[index] = copy_rhs.data[index];
    }
    return *this;
}

// Move assignment operator
matrix& matrix::operator=(matrix&& move_rhs){
    if(this != &move_rhs){
        delete[] data;
        num_of_columns = move_rhs.num_of_columns;
        num_of_rows = move_rhs.num_of_rows;
        size = move_rhs.size; 
        data = move_rhs.data;
        move_rhs.data = nullptr;
    }
    return *this;
}

// Destructor
matrix::~matrix(){
    delete[] data;
}

matrix transpose(const matrix& trans_rhs){
    matrix result(trans_rhs.num_of_rows, trans_rhs.num_of_columns);
    for(unsigned long long index_x = 0; index_x < trans_rhs.num_of_columns; index_x++){
        for(unsigned long long index_y = 0; index_y < trans_rhs.num_of_rows; index_y++){
            result.data[index_y + index_x * trans_rhs.num_of_rows] = trans_rhs.data[index_x + index_y * trans_rhs.num_of_columns];
        }
    }
    return result;
}

void matrix::print(){
    for(unsigned long long index = 0; index < size; index++){
        if(index % num_of_columns == 0)
            std::cout << std::endl;
        std::cout << data[index] << ' ';
    }
}

void matrix::map_function(std::function<double(double)> func){
    for(unsigned long long index = 0; index < size; index++)
        data[index] = func(data[index]);
}

matrix operator+(const matrix& add_lhs, const matrix& add_rhs){
    if(add_lhs.num_of_columns != add_rhs.num_of_columns || add_lhs.num_of_rows != add_rhs.num_of_rows) 
        exit(87);
    matrix result(add_lhs);
    for(unsigned long long index = 0; index < result.size; index++)
        result.data[index] += add_rhs.data[index];
    return result;
}

matrix operator-(const matrix& sub_lhs, const matrix& sub_rhs){
    if(sub_lhs.num_of_columns != sub_rhs.num_of_columns || sub_lhs.num_of_rows != sub_rhs.num_of_rows) 
        exit(87);
    matrix result(sub_lhs);
    for(unsigned long long index = 0; index < result.size; index++)
        result.data[index] -= sub_rhs.data[index];
    return result;
}

matrix operator*(const matrix& mult_lhs, const matrix& mult_rhs){
    if(mult_lhs.num_of_columns != mult_rhs.num_of_columns || mult_lhs.num_of_rows != mult_rhs.num_of_rows) 
        exit(87);
    matrix result(mult_lhs);
    for(unsigned long long index = 0; index < result.size; index++)
        result.data[index] *= mult_rhs.data[index];
    return result;
}

matrix dot(const matrix& dot_lhs, const matrix& dot_rhs){
    if(dot_lhs.num_of_columns != dot_rhs.num_of_rows) 
        exit(87);
    matrix result(dot_rhs.num_of_columns, dot_lhs.num_of_rows);
    for(int column = 0; column < dot_rhs.num_of_columns; column++){
        for(int row = 0; row < dot_lhs.num_of_rows; row++){
            double sum = 0;
            for(int k = 0; k < dot_lhs.num_of_columns; k++){
                sum += dot_lhs.data[k + row * dot_lhs.num_of_columns] * dot_rhs.data[column + k * dot_rhs.num_of_columns];
            }
            result.data[column + row * result.num_of_columns] = sum;
        }
    }
    return result;
}

matrix::operator std::vector<double>() const{
    return std::vector<double>(data, data + size);
}