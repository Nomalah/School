#ifndef MATRIX_H
#define MATRIX_H

#include <functional>

class matrix
{
    public:
        int rows;
		int cols;
		float** data = nullptr;
		std::string name;
        matrix(int initRows, int initCols, std::string name = "Default");
		matrix(float arr[], int arrSize, std::string name = "Default");
		void setTo(matrix obj);
		void destroyMatrix();
        void mapFunc(std::function <float(float,int,int)> func);
        void print();
        void randomize();
        matrix copy();
        matrix transpose();
        float* toArray(bool delMatrix = false);
        void fromArray(float arr[], int arrSize);
        matrix operator+ (matrix &obj);
        matrix operator- (matrix &obj);
        matrix operator* (matrix &obj);
        matrix operator= (matrix obj);
        matrix dot(matrix &obj);

};


#endif // MATRIX_H

