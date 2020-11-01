#pragma once
#include <vector>
#include <iostream>

class Matrix
{
public:
	Matrix(std::size_t n, std::size_t m);
	// explicit Matrix(const Matrix&);

	Matrix(Matrix&&);
	Matrix& operator = (Matrix&&);
	~Matrix();

	std::size_t* operator [](std::size_t i) { return data[i]; }
	const std::size_t* operator [](std::size_t i) const { return data[i]; }

	std::size_t N() const { return n; }
	std::size_t M() const { return m; }

	std::size_t** GetData() { return data; }

private:
	std::size_t* buffer = nullptr;
	std::size_t** data = nullptr;

	std::size_t n;
	std::size_t m;
};

std::ostream& operator << (std::ostream& out, const Matrix& matr);