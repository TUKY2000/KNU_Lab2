//
// Created By Ivan Martsilenko and Arthur Onyshkevych
//
//
// All rights reserved
//

#include "Matrix.h"
#include <string>
#include <iostream>

CMatrix::CMatrix()
	: cols(1)
	, rows(1)
{
	create();
}

CMatrix::CMatrix(const unsigned int _rows, const unsigned _cols)
	: cols(_cols)
	, rows(_rows)
{
	create();
}

CMatrix::CMatrix(const unsigned int _rows, const unsigned _cols, const double num)
	: cols(_cols)
	, rows(_rows)
{
	create();
	setElemNum(num);
}

CMatrix::CMatrix(const CMatrix & other)
{
	if (*this == other)
		throw std::logic_error("");
	else
		*this = other;
}

CMatrix::CMatrix(CMatrix && other)
{
	if (*this == other)
		throw std::logic_error("");
	else
	{
		*this = other;
		delete other.mass;
		other.mass = nullptr;
	}
}

CMatrix::~CMatrix()
{
	if (mass != nullptr)
		delete mass;
}


void CMatrix::create()
{
	mass = new double[rows * cols];
}

void CMatrix::nulify()
{
	setElemNum(0);
}

void CMatrix::setElemNum(const double num)
{
	for (size_t row = 0; row < rows; ++row)
	{
		for (size_t col = 0; col < cols; ++col)
		{
			(mass + row * cols)[col] = num;
		}
	}
}

// added for Jakobi method 
void CMatrix::symmetricalRandomMatrixValues()
{
	for (size_t col = 0; col < cols; ++col)
	{
		for (size_t row = 0; row < rows - col; ++row)
		{
			(mass + row * cols)[col] = ((-1) ^ rand()) *(rand() % 5);
			(mass + row * cols)[row] = (mass + row * cols)[col];
		}
	}
}

CMatrix & CMatrix::operator|(const CMatrix & other)
{
	if (rows != other.getRows()) throw std::logic_error("");
	CMatrix * res = new CMatrix(rows, cols + other.getCols(), 0);
	double num = 0;
	size_t col = 0;
	for (size_t row = 0; row < rows; ++row)
	{
		col = 0;
		for (; col < cols; ++col)
		{
			num = (mass + row * cols)[col];
			(*res)[row][col] = (mass + row * cols)[col];
		}
		for (; col < res->getCols(); ++col)
		{
			num = other[row][col - cols];
			(*res)[row][col] = other[row][col - cols];
		}
	}
	return *res;
}

void CMatrix::randomMatrixValues()
{
	for (size_t col = 0; col < cols; ++col)
	{
		for (size_t row = 0; row < rows; ++row)
		{
			(mass + row * cols)[col] = ((-1) ^ rand()) *(rand() % 5);
		}
	}
}

unsigned int const CMatrix::getRows() const
{
	return rows;
}

unsigned int const CMatrix::getCols() const
{
	return cols;
}

void CMatrix::setSize(const unsigned int _rows, const unsigned _cols)
{
	cols = _cols;
	rows = _rows;
	create();
}

CMatrix & CMatrix::operator=(const CMatrix & other)
{
	cols = other.getCols();
	rows = other.getRows();
	create();
	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
			(mass + row * cols)[col] = other[row][col];
	return *this;
}

bool CMatrix::operator==(const CMatrix & other) const
{
	if (mass == nullptr) return false;
	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
			if ((mass + row * rows)[col] != other[row][col])
				return false;
	return true;
}

CMatrix & CMatrix::operator+(const CMatrix & other)
{
	if (this->cols != other.getCols() || this->rows != other.getRows())
		throw std::logic_error("");
	CMatrix * matrNew = new CMatrix(this->rows, this->cols);
	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
			(*matrNew)[row][col] = (mass + row * rows)[col] + other[row][col];
	return *matrNew;
}

CMatrix & CMatrix::operator-(const CMatrix & other)
{
	if (this->cols != other.getCols() || this->rows != other.getRows())
		throw std::logic_error("");
	CMatrix * matrNew = new CMatrix(this->rows, this->cols);
	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
			(*matrNew)[row][col] = (mass + row * rows)[col] - other[row][col];
	return *matrNew;
}

CMatrix & CMatrix::operator*(const CMatrix & other)
{
	if (this->cols != other.getRows())
		throw std::logic_error("");
	CMatrix * matrNew = new CMatrix(this->rows, other.getCols(), 0);
	for (size_t row = 0; row < matrNew->getRows(); ++row)
	{
		for (size_t col = 0; col < matrNew->getCols(); ++col)
		{
			for (size_t inner = 0; inner < this->cols; ++inner)
			{
				(*matrNew)[row][col] += (mass + row * cols)[inner] * other[inner][col];
			}
		}
	}
	return *matrNew;
}

CMatrix & CMatrix::operator*(const double & num)
{
	CMatrix * matrNew = new CMatrix(this->rows, this->cols);
	for (size_t row = 0; row < matrNew->getRows(); ++row)
	{
		for (size_t col = 0; col < matrNew->getCols(); ++col)
		{
			(*matrNew)[row][col] = (mass + row * rows)[col] * num;
		}
	}
	return *matrNew;
}

CMatrix & CMatrix::operator~()
{
	CMatrix *res = new CMatrix(cols, rows, 0);
	for (unsigned int row = 0; row < rows; ++row)
	{
		for (unsigned int col = 0; col < cols; ++col)
		{
			(*res)[col][row] = (mass + row * cols)[col];
		}
	}
	return *res;
}

double * CMatrix::operator[](const int & row) const
{
	return (mass + row * cols);
}

std::ostream & operator<<(std::ostream & output, const CMatrix & matr)	//	!!!
{
	size_t row = 0
		, col = 0;
	for (; row < matr.getRows() - 1; ++row)
	{
		output << "||";
		for (col = 0; col < matr.getCols() - 1; ++col)
		{
			output << matr[row][col] << "\t";
		}
		output << matr[row][col] << "||\n";
	}
	output << "||";
	for (col = 0; col < matr.getCols() - 1; ++col)
	{
		output << matr[row][col] << "\t";
	}
	output << matr[row][col] << "||";
	return output;
}

std::istream & operator >> (std::istream & input, CMatrix & matr)
{
	std::string snum;
	for (size_t row = 0; row < matr.getRows(); ++row)
	{
		std::cout << "Please input row number " << row << "." << std::endl;
		for (size_t col = 0; col < matr.getCols(); ++col)
		{
			std::cout << "Please input value of x[" << row << "][" << col << "] " << ":";
			input >> snum;
			matr[row][col] = std::atol(snum.c_str());
			std::cout << std::endl;
		}
	}
	return input;
}

// Jakobi
bool CMatrix::isSymmetrical(CMatrix & other) // maybe ,mistake with parameter 
{
	bool result = true;
	for (int col = 0; col < other.getCols(); col++)
	{
		for (int row = col; row < other.getRows() - col; row++)
		{
			if (other[col][row] != other[row][col])
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

CMatrix & CMatrix::unitary(const unsigned int & dim)
{
	CMatrix * res = new CMatrix(dim, dim, 0);

	for (size_t row = 0; row < dim; ++row)
	{
		(*res)[row][row] = 1;
	}
	return *res;
}

void CMatrix::createGilbertMatrix()
{
	for (size_t col = 0; col < cols; ++col)
	{
		for (size_t row = 0; row < rows; ++row)
		{
			(mass + row * cols)[col] = 1.0 / (row + col + 1);
		}
	}
}