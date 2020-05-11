#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <functional>

// matrix class
class matrix{
    private:
        unsigned num_of_columns;
        unsigned num_of_rows;
        unsigned long long size;
        double* data; // Data is stored linearly (x + y * num_of_columns)
    public:
        // Normal constructor
        matrix(unsigned initial_columns = 0, unsigned initial_rows = 0);
        
        // Copy constructor
        matrix(const matrix& copy_src);

        // Move constructor
        matrix(matrix&& move_src);

        // Copy assignment operator
        matrix& operator=(const matrix& copy_rhs);
        
        // Move assignment operator
        matrix& operator=(matrix&& move_rhs);

        // Destructor
        ~matrix();

        void map_function(std::function<double(double)> func);
        void print();

        operator std::vector<double>() const;

        friend matrix transpose(const matrix& trans_rhs);

        friend matrix operator+(const matrix& add_lhs, const matrix& add_rhs);
        friend matrix operator-(const matrix& sub_lhs, const matrix& sub_rhs);
        friend matrix operator*(const matrix& mult_lhs, const matrix& mult_rhs);
        friend matrix dot(const matrix& dot_lhs, const matrix& dot_rhs);
};

matrix transpose(const matrix& trans_rhs);

matrix operator+(const matrix& add_lhs, const matrix& add_rhs);
matrix operator-(const matrix& sub_lhs, const matrix& sub_rhs);
matrix operator*(const matrix& mult_lhs, const matrix& mult_rhs);
matrix dot(const matrix& dot_lhs, const matrix& dot_rhs);

#endif // MATRIX_H