#include <iostream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <thread>
#include "matrix.h"

using namespace std;

matrix::matrix(int initRows, int initCols, string name)
{
    rows = initRows;
    cols = initCols;
    this -> name = name;
    data = new float* [rows];
    for (int y = 0; y < rows; y++)
    {
        data[y] = new float [cols];
        for (int x = 0; x < cols; x++)
        {
            data[y][x] = 0;
        }
    }
    //cout << "Created " << name << endl;
}

matrix::matrix(float arr[], int arrSize, string name)
{
    this -> name = name;
    fromArray(arr, arrSize);
    //cout << "Created " << name << endl;
}

void matrix::fromArray(float arr[], int arrSize)
{
    //cout << data;
    if (data != nullptr)
    {
        destroyMatrix();
    }
    rows = arrSize;
    cols = 1;
    data = new float* [rows];
    for (int y = 0; y < rows; y++)
    {
        data[y] = new float [cols];
        for (int x = 0; x < cols; x++)
        {
            data[y][x] = arr[y];
        }
    }
}

void matrix::destroyMatrix()
{
    //cout << name << " Destructor" << endl;
    for (int y = 0; y < rows; y++)
    {
        delete [] data[y];
    }
    delete [] data;
    return;
}


void matrix::mapFunc(function <float(float,int,int)> func)
{
    /*thread* rowThreads = new thread[rows];
    for (int y = 0; y < rows; y++)
    {
        rowThreads[y] = thread(mapRow, y, *this, func);
    }*/
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            float val = data[y][x];
            data[y][x] = func(val, x, y);
        }
    }
    /*for (int y = 0; y < rows; y++)
    {
        rowThreads[y].join();
    }
    delete [] rowThreads;*/
    return;
}

void matrix::print()
{
    this -> mapFunc([](float v, int x, int y) -> float
    {
        if (x == 0)
        {
            cout << endl;
        }
        cout << v << " ";
        return v;
    });
    cout << endl;
    return;
}

void matrix::randomize()
{
    srand((unsigned int)time(0)+rand());
    mapFunc([](float v, int x, int y) -> float{return (((float)rand()+1)/((float)rand()+1));});
    return;
}

matrix matrix::copy()
{
    matrix m (rows, cols);
    m.mapFunc([=](float v, int x, int y) -> float{return data[y][x];});
    return m;
}

void matrix::setTo(matrix obj)
{
    if(this != &obj)
    {
        this -> destroyMatrix();

        rows = obj.rows;
        cols = obj.cols;

        data = new float* [rows];
        for (int y = 0; y < rows; y++)
        {
            data[y] = new float [cols];
            for (int x = 0; x < cols; x++)
            {
                data[y][x] = obj.data[y][x];
            }
        }

    }
    obj.destroyMatrix();
}

matrix matrix::transpose()
{
    matrix m (cols, rows);
    m.mapFunc([=](float v, int x, int y)
    {
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

matrix matrix::operator+ (matrix &obj)
{
    if (rows != obj.rows || cols != obj.cols)
    {
        cout << "The rows & columms of the matrix operands need to be the same. (Matrix -> addition operator))" << "\nRows of Operand A:" << rows << "\nRows of Operand B:" << obj.rows << "\nColumms of Operand A:" << cols << "\nColumms of Operand B:" << obj.cols << "\n";
        exit(87);
    }
    matrix result(rows, cols, "Result+");
    result.mapFunc([=](float v, int x, int y) -> float{return data[y][x] + obj.data[y][x];});
    return result;
}

matrix matrix::operator- (matrix &obj)
{
    if (rows != obj.rows || cols != obj.cols)
    {
        cout << "The rows & columms of the matrix operands need to be the same. (Matrix -> subtraction operator)" << "\nRows of Operand A:" << rows << "\nRows of Operand B:" << obj.rows << "\nColumms of Operand A:" << cols << "\nColumms of Operand B:" << obj.cols << "\n";
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
            sum += data[y]
            [k] * obj.data[k][x];
        }
        return sum;});

    return result;
}

matrix matrix::operator=(matrix obj)
{
    if(this != &obj)
    {
        this -> destroyMatrix();

        rows = obj.rows;
        cols = obj.cols;

        data = new float* [rows];
        for (int y = 0; y < rows; y++)
        {
            data[y] = new float [cols];
            for (int x = 0; x < cols; x++)
            {
                data[y][x] = obj.data[y][x];
            }
        }

    }
    return *this;
}
