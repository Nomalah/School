#ifndef MATRIX_H
#define MATRIX_H

#include <vector>


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
        matrix(const std::vector<double>& vec_init);
        
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

        template<class map_operator>
        void map_function(map_operator func);
        void print();

        operator std::vector<double>() const;

        friend matrix transpose(const matrix& trans_rhs);

        friend matrix operator+(const matrix& add_lhs, const matrix& add_rhs);
        friend matrix operator-(const matrix& sub_lhs, const matrix& sub_rhs);
        friend matrix operator*(const matrix& mult_lhs, const matrix& mult_rhs);
        friend matrix dot(const matrix& dot_lhs, const matrix& dot_rhs);
};



#endif // MATRIX_H