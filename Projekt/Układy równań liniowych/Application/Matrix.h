#pragma once
#include <iostream>
#include <assert.h>

class matrix {
private:
	double **M;

public:
	int rows;
	int cols;

	void init(int a1, int a2, int a3) {
		for (int i = 0; i < rows - 2; i++) {
			for (int j = 0; j < cols - 2; j++) {
				if (i == j) {
					M[i][j] = a1;
					M[i + 1][j] = M[i][j + 1] = a2;
					M[i + 2][j] = M[i][j + 2] = a3;
				}
			}
		}
		M[rows - 2][cols - 2] = M[rows - 1][cols - 1] = a1;
		M[rows - 1][cols - 2] = M[rows - 2][cols - 1] = a2;
	}

	static double norm(matrix m) {
		assert(m.cols == 1);
		double val = 0.0;
		for (int i = 0; i < m.rows; i++) {
			val += pow(m[i][0], 2);
		}
		return sqrt(val);
	}
	void allocMemory() {
		M = new double*[rows];
		for (int i = 0; i < rows; i++)
			M[i] = new double[cols];

	}
	matrix() : rows(1), cols(1) {
		allocMemory();
		M[0][0] = 0;
	}
	matrix(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
		allocMemory();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				M[i][j] = 0;
			}
		}
	}
	matrix(const matrix& m) {
		this->rows = m.rows;
		this->cols = m.cols;
		allocMemory();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				M[i][j] = m[i][j];
			}
		}
	}
	~matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] M[i];
		}
		delete[] M;
	}

	////////////////////////////////////////////////////////////
	/// Operators
	////////////////////////////////////////////////////////////
	matrix& operator=(const matrix& m) {
		if (this == &m) {
			return *this;
		}
		this->~matrix();
		this->rows = m.rows;
		this->cols = m.cols;
		allocMemory();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				M[i][j] = m[i][j];
			}
		}
		return *this;
	}
	matrix& operator+=(const matrix& m)
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				M[i][j] += m[i][j];
			}
		}
		return *this;
	}
	matrix& operator-=(const matrix& m)
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				M[i][j] -= m[i][j];
			}
		}
		return *this;
	}
	matrix& operator*=(const matrix& m){
		matrix temp(rows, m.cols);
		for (int i = 0; i < temp.rows; ++i) {
			for (int j = 0; j < temp.cols; ++j) {
				for (int k = 0; k < cols; ++k) {
					temp[i][j] += (M[i][k] * m[k][j]);
				}
			}
		}
		return (*this = temp);
	}
	matrix& operator*=(double num)
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				M[i][j] *= num;
			}
		}
		return *this;
	}
	matrix& operator-() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (M[i][j] != 0)
					M[i][j] = -M[i][j];
			}
		}
		return *this;
	}

	double* operator[](size_t el) {
		return M[el];
	}
	double* operator[](size_t el)const {
		return M[el];
	}
	friend std::ostream & operator <<(std::ostream & strumien, const matrix & m) {
		for (int i = 0; i < m.rows; i++) {
			for (int j = 0; j < m.cols; j++) {
				strumien << m[i][j] << " ";
			}
			strumien << std::endl;
		}
		return strumien;
	}
};

matrix operator+(const matrix& m1, const matrix& m2)
{
	matrix temp(m1);
	return (temp += m2);
}
matrix operator-(const matrix& m1, const matrix& m2)
{
	matrix temp(m1);
	return (temp -= m2);
}
matrix operator*(const matrix& m1, const matrix& m2)
{
	matrix temp(m1);
	return (temp *= m2);
}
matrix operator*(const matrix& m, double num)
{
	matrix temp(m);
	return (temp *= num);
}
matrix operator*(double num, const matrix& m)
{
	return (m * num);
}
