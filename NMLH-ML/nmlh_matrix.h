#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <array>

template <size_t rows, size_t columns, typename T = double>
class matrix {
public:
	matrix(const std::array<rows * columns>& vec_init) :
		data { vec_init } {};

	double* begin() { return data; }
	double* end() { return data + rows * columns; }

	matrix<columns, rows> transpose();

	template <typename map_func>
	void apply(map_func func) {
		for (auto& val : *this) {
			val = func(val);
		}
	}

	template <size_t op_rows, size_t op_columns>
	friend matrix<op_rows, op_columns> operator+(const matrix<op_rows, op_columns>& add_lhs, const matrix<op_rows, op_columns>& add_rhs);
	template <size_t op_rows, size_t op_columns>
	friend matrix<op_rows, op_columns> operator-(const matrix<op_rows, op_columns>& sub_lhs, const matrix<op_rows, op_columns>& sub_rhs);
	template <size_t op_rows, size_t op_columns>
	friend matrix<op_rows, op_columns> operator*(const matrix<op_rows, op_columns>& mult_lhs, const matrix<op_rows, op_columns>& mult_rhs);

	template <size_t op1_rows, size_t op1_columns, size_t op2_columns>
	friend matrix<op1_rows, op2_columns> dot(const matrix<op1_rows, op1_columns>& dot_lhs, const matrix<op1_columns, op2_columns>& dot_rhs);

private:
	std::array<T, rows * columns> data;
};

#include <iostream>

template <size_t rows, size_t columns>
matrix<columns, rows> matrix<rows, columns>::transpose() {
	matrix<columns, rows> result({});
	for (unsigned long long index_x = 0; index_x < columns; index_x++) {
		for (unsigned long long index_y = 0; index_y < rows; index_y++) {
			result.data[index_y + index_x * rows] = trans_rhs.data[index_x + index_y * columns];
		}
	}
	return result;
}

template <size_t op_rows, size_t op_columns>
matrix<op_rows, op_columns> operator+(const matrix<op_rows, op_columns>& add_lhs, const matrix<op_rows, op_columns>& add_rhs) {
	matrix<op_rows, op_columns> result(add_lhs);
	for (unsigned long long index = 0; index < result.size; index++)
		result.data[index] += add_rhs.data[index];
	return result;
}

template <size_t op_rows, size_t op_columns>
matrix operator-(const matrix& sub_lhs, const matrix& sub_rhs) {
	matrix result(sub_lhs);
	for (unsigned long long index = 0; index < result.size; index++)
		result.data[index] -= sub_rhs.data[index];
	return result;
}

template <size_t op_rows, size_t op_columns>
matrix operator*(const matrix& mult_lhs, const matrix& mult_rhs) {
	matrix result(mult_lhs);
	for (unsigned long long index = 0; index < result.size; index++)
		result.data[index] *= mult_rhs.data[index];
	return result;
}

template <size_t op1_rows, size_t op1_columns, size_t op2_columns>
matrix dot(const matrix& dot_lhs, const matrix& dot_rhs) {
	matrix result(dot_rhs.num_of_columns, dot_lhs.num_of_rows);
	for (int column = 0; column < dot_rhs.num_of_columns; column++) {
		for (int row = 0; row < dot_lhs.num_of_rows; row++) {
			double sum = 0;
			for (int k = 0; k < dot_lhs.num_of_columns; k++) {
				sum += dot_lhs.data[k + row * dot_lhs.num_of_columns] * dot_rhs.data[column + k * dot_rhs.num_of_columns];
			}
			result.data[column + row * result.num_of_columns] = sum;
		}
	}
	return result;
}

#endif    // MATRIX_H