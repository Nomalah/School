#ifndef MATRIX_H
#define MATRIX_H

#include <functional>

class matrix{
    public:
        int rows;
		int cols;
		float** data;
		std::string name;
        matrix(int initRows, int initCols, std::string name = "Default");
		matrix(float arr[], int arrSize, std::string name = "Default");

        // Maps a function to all members of the matrix
        void mapFunc(std::function <float(float,int,int)> func);
        // Built in print function
        void print();
        // Built in randomize function
        void randomize();
        
        // Converts a matrix to an array or create a matrix from an array
        float* toArray(bool delMatrix = false);
        void fromArray(float arr[], int arrSize);

        // Transposes the maxtrix (switches x and y)
        matrix transpose();

        // Destructor
		void destroyMatrix();
        ~matrix();

        // Copy constructor
        matrix copy();
        matrix(const matrix& copy_src);

        // Move constructor
        //matrix(matrix&& move_src);
        // Copy assignment
        matrix& operator= (const matrix& copy_rhs);


        // Move assignment
		void setTo(matrix obj);
        matrix& operator=(matrix&& move_rhs);
        
        // Add two matrices
        matrix operator+ (matrix& obj);
        matrix operator- (matrix& obj);
        matrix operator* (matrix& obj);

        // Dot multiplication
        matrix dot(matrix& obj);

};


#endif // MATRIX_H
