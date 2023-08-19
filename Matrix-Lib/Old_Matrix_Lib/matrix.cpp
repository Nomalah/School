#include <iostream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <thread>
#include "matrix.h"

using namespace std;

matrix::matrix(int initRows, int initCols, string name) : data(nullptr), rows(initRows), cols(initCols), name(name){
    data = new float* [rows];
    for (int y = 0; y < rows; y++)
    {
        data[y] = new float [cols];
        for (int x = 0; x < cols; x++)
        {
            data[y][x] = 0;
        }
    }
}

matrix::matrix(float arr[], int arrSize, string name) : data(nullptr), name(name){
    fromArray(arr, arrSize);
}

void matrix::fromArray(float arr[], int arrSize){
    if (data != nullptr){
        destroyMatrix();
    }
    rows = arrSize;
    cols = 1;
    data = new float* [rows];
    for (int y = 0; y < rows; y++){
        data[y] = new float [cols];
        for (int x = 0; x < cols; x++){
            data[y][x] = arr[y];
        }
    }
}

void matrix::destroyMatrix(){
    for (int y = 0; y < rows; y++){
        delete [] data[y];
    }
    delete [] data;
}

matrix::~matrix(){
    /*for (int y = 0; y < rows; y++){
        delete [] data[y];
    }
    delete [] data;*/
}


void matrix::mapFunc(function <float(float,int,int)> func){
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            data[y][x] = func(data[y][x], x, y);
        }
    }
}

void matrix::print(){
    this->mapFunc([](float v, int x, int y) -> float{
        if (x == 0){
            cout << endl;
        }
        cout << v << " ";
        return v;
    });
    cout << endl;
}

void matrix::randomize(){
    srand((unsigned int)time(0)+rand());
    mapFunc([](float v, int x, int y) -> float{return (((float)rand()+1)/((float)rand()+1));});
}

matrix matrix::copy()
{
    matrix m (rows, cols);
    m.mapFunc([=](float v, int x, int y) -> float{return data[y][x];});
    return m;
}

matrix::matrix(const matrix& copy_src) : rows(copy_src.rows), cols(copy_src.cols), name(copy_src.name){
    data = new float* [rows];
    for (int y = 0; y < rows; y++){
        data[y] = new float [cols];
        for (int x = 0; x < cols; x++){
            data[y][x] = copy_src.data[y][x];
        }
    }
}

void matrix::setTo(matrix obj){
    if(this != &obj){
        this -> destroyMatrix();

        rows = obj.rows;
        cols = obj.cols;

        data = new float* [rows];
        for (int y = 0; y < rows; y++){
            data[y] = new float [cols];
            for (int x = 0; x < cols; x++){
                data[y][x] = obj.data[y][x];
            }
        }
    }
    obj.destroyMatrix();
}


matrix& matrix::operator=(const matrix& copy_rhs){
    if(this != &copy_rhs){
        for(int y = 0; y < rows; y++){
            delete[] this->data[y];
        }
        delete[] this->data;

        this->rows = copy_rhs.rows;
        this->cols = copy_rhs.cols;

        this->data = new float* [rows];
        for (int y = 0; y < rows; y++){
            this->data[y] = new float [cols];
            for (int x = 0; x < cols; x++){
                this->data[y][x] = copy_rhs.data[y][x];
            }
        }

    }
    return *this;
}

matrix& matrix::operator=(matrix&& move_rhs){
    if(this != &move_rhs){
        for(int y = 0; y < rows; y++){
            delete[] this->data[y];
        }
        delete[] this->data;

        this->rows = move_rhs.rows;
        this->cols = move_rhs.cols;

        this->data = move_rhs.data;
        for (int y = 0; y < rows; y++){
            this->data[y] = move_rhs.data[y];
            for (int x = 0; x < cols; x++){
                this->data[y][x] = move_rhs.data[y][x];
            }
            move_rhs.data[y] = nullptr;
        }
        move_rhs.data = nullptr;
    }
    return *this;
}


matrix matrix::transpose(){
    matrix m (cols, rows);
    m.mapFunc([=](float v, int x, int y){
        return data[x][y];
    });
    return m;
}

float* matrix::toArray(bool delMatrix)
{
    float* arr = new float[rows*cols];
    mapFunc([=](float v, int x, int y) -> float{arr[x+y*cols] = v; return v;});
    if (delMatrix)
        destroyMatrix();
    return arr;
}

matrix matrix::operator+ (matrix& obj){
    if (rows != obj.rows || cols != obj.cols){
        cout << "The rows & columms of the matrix operands need to be the same. (Matrix -> addition operator))" << "\nRows of Operand A:" << rows << "\nRows of Operand B:" << obj.rows << "\nColumms of Operand A:" << cols << "\nColumms of Operand B:" << obj.cols << "\n";
        exit(87);
    }
    matrix result(rows, cols, "Result+");
    result.mapFunc([=](float v, int x, int y) -> float{return data[y][x] + obj.data[y][x];});
    return result;
}

matrix matrix::operator- (matrix& obj){
    if (rows != obj.rows || cols != obj.cols){
        cout << "The rows & columms of the matrix operands need to be the same. (Matrix -> subtraction)" << "\nRows of Operand A:" << rows << "\nRows of Operand B:" << obj.rows << "\nColumms of Operand A:" << cols << "\nColumms of Operand B:" << obj.cols << "\n";
        exit(87);
    }
    matrix result (rows, cols, "Result-");
    result.mapFunc([=](float v, int x, int y) -> float{return data[y][x] - obj.data[y][x];});
    return result;
}

matrix matrix::operator* (matrix &obj)
{
    if (rows != obj.rows || cols != obj.cols)
    {
        cout << "The rows & columms of the matrix operands need to be the same. (Matrix -> multiplication operator)" << "\nRows of Operand A:" << rows << "\nRows of Operand B:" << obj.rows << "\nColumms of Operand A:" << cols << "\nColumms of Operand B:" << obj.cols << "\n";
        exit(87);
    }
    matrix result (rows, cols, "Result*");
    result.mapFunc([=](float v, int x, int y) -> float{return data[y][x] * obj.data[y][x];});
    return result;
}

matrix matrix::dot(matrix &obj)
{
    if (cols != obj.rows)
    {
        cout << "The number of columms in the first operand must equal the number of rows in the second operand. (Matrix -> dot multiplication)\n";
        exit(87);
    }
    matrix result (rows, obj.cols, "Result Dot");
    result.mapFunc([=](float v, int x, int y) -> float
    {
        float sum = 0;
        for (int k = 0; k < cols; k++)
        {
            sum += data[y][k] * obj.data[k][x];
        }
        return sum;
    });

    return result;
}
