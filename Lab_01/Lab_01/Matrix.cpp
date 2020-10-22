#include "Matrix.h"

Matrix::Matrix(std::size_t n, std::size_t m) 
	: n(n), m(m)
{
	buffer = new std::size_t[n * m];
	data = new std::size_t * [n];
	for (size_t i = 0; i < n; i++)
		data[i] = buffer + i * m;
}


Matrix& Matrix::operator = (Matrix&& matr)
{
	delete[] buffer;
	delete[] data;

	buffer = matr.buffer;
	data = matr.data;
	n = matr.n;
	m = matr.m;

	matr.data = nullptr;
	matr.buffer = nullptr;
	return *this;
}

/*Matrix::Matrix(const Matrix& matr)
	: n(matr.n), m(matr.m)
{
	buffer = new std::size_t[n * m];
	data = new std::size_t * [n];
	for (size_t i = 0; i < n; i++)
		data[i] = buffer + i * m;

	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++)
			data[i][j] = matr.data[i][j];
}*/

Matrix::Matrix(Matrix&& matr)
{
	*this = std::move(matr);
}

Matrix::~Matrix()
{
	delete[] buffer;
	delete[] data;
}

std::ostream& operator << (std::ostream& out, const Matrix& matr)
{
	for (size_t i = 0; i < matr.N(); i++)
	{
		for (size_t j = 0; j < matr.M(); j++)
			out << matr[i][j] << " ";
		out << std::endl;
	}
	return out;
}