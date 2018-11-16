//
// Created By Ivan Martsilenko and Arthur Onyshkevych
//
//
// All rights reserved
//

#include "Matrix.h"
#include <string>
#include <iostream>
#include <ctime>

CMatrix::CMatrix()
	: cols(1)
	, rows(1)
	, mass(nullptr)
	, redcode(nullptr)
{
	create();
}

CMatrix::CMatrix(const unsigned int _rows, const unsigned _cols)
	: cols(_cols)
	, rows(_rows)
	, mass(nullptr)
	, redcode(nullptr)
{
	create();
}

CMatrix::CMatrix(const unsigned int _rows, const unsigned _cols, const double num)
	: cols(_cols)
	, rows(_rows)
	, mass(nullptr)
	, redcode(nullptr)
{
	create();
	setElemNum(num);
}

CMatrix::CMatrix(const CMatrix & other)
	: mass(nullptr)
	, redcode(nullptr)
{
	if (this == &other)
		throw std::logic_error("");

	*this = other;
}

CMatrix::CMatrix(CMatrix && other)
	: mass(nullptr)
	, redcode(nullptr)
{
	if (this == &other)
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
	{
		delete[] mass;
	}
		
	if (redcode != nullptr) 
	{ 
		delete redcode; 
		redcode = nullptr;
	}
		
}


void CMatrix::create()
{
	if (this->mass != nullptr) delete this->mass;
	this->mass = new double[rows * cols];

	redcode = nullptr;
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

// added for Jacobi method 
void CMatrix::symmetricalRandomMatrixValues()
{
	srand((unsigned int)time(0));
	for (size_t row = 0; row < rows; ++row)
	{
		for (size_t col = row; col < cols; ++col)
		{
			(mass + row * cols)[col] = (pow((-1), rand())) *(rand() % 5);
			(mass + col * cols)[row] = (mass + row * cols)[col];
		}
	}
}

CMatrix * CMatrix::operator|(const CMatrix & other) const
{
	if (rows != other.getRows()) throw std::logic_error("");
	
	//if (redcode != nullptr)	delete redcode;
	//redcode = new CMatrix(rows, cols + other.getCols(), 0);
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
	return res;
}

void CMatrix::randomMatrixValues()
{
	srand((unsigned int)time(0));
	for (size_t col = 0; col < cols; ++col)
	{
		for (size_t row = 0; row < rows; ++row)
		{
			(mass + row * cols)[col] = (pow((-1), rand())) *(rand() % 5);
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

CMatrix CMatrix::operator+(const CMatrix & other)
{
	if (this->cols != other.getCols() || this->rows != other.getRows())
		throw std::logic_error("");

	//if (redcode != nullptr)	delete redcode;
	//redcode = new CMatrix(rows, cols, 0);

	CMatrix res(this->rows, this->cols);
	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
			(res)[row][col] = (mass + row * rows)[col] + other[row][col];

	return res;
}

CMatrix CMatrix::operator-(const CMatrix & other)
{
	if (this->cols != other.getCols() || this->rows != other.getRows())
		throw std::logic_error("");

	//if (redcode != nullptr)	delete redcode;
	//redcode = new CMatrix(rows, cols, 0);

	CMatrix res(this->rows, this->cols);
	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
			(res)[row][col] = (mass + row * cols)[col] - other[row][col];

	return res;
}

CMatrix CMatrix::operator*(const CMatrix & other)
{
	if (this->cols != other.getRows())
		throw std::logic_error("");

	//if (redcode != nullptr)	delete redcode;
	//redcode = new CMatrix(rows, other.getCols(), 0);

	CMatrix res(this->rows, other.getCols(), 0);
	for (size_t row = 0; row < res.getRows(); ++row)
	{
		for (size_t col = 0; col < res.getCols(); ++col)
		{
			for (size_t inner = 0; inner < this->cols; ++inner)
			{
				(res)[row][col] += (mass + row * cols)[inner] * other[inner][col];
			}
		}
	}

	return res;
}

CMatrix CMatrix::operator*(const double & num)
{
	//if (redcode != nullptr)	delete redcode;
	//redcode = new CMatrix(rows, cols, 0);

	CMatrix res(this->rows, this->cols);
	for (size_t row = 0; row < res.getRows(); ++row)
	{
		for (size_t col = 0; col < res.getCols(); ++col)
		{
			(res)[row][col] = (mass + row * rows)[col] * num;
		}
	}
	return res;
}

CMatrix CMatrix::operator~()
{
	CMatrix res(cols, rows, 0);
	//if (redcode != nullptr)	delete redcode;
	//redcode = new CMatrix(cols, rows, 0);

	double temp = 0;

	for (unsigned int row = 0; row < rows; ++row)
	{
		for (unsigned int col = 0; col < cols; ++col)
		{
			(res)[col][row] = (mass + row * cols)[col];
		}
	}

	return res;
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
			matr[row][col] = std::atof(snum.c_str());
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

CMatrix CMatrix::unitary(const unsigned int & dim)
{
	//if (redcode != nullptr)	delete redcode;
	//redcode = new CMatrix(dim, dim, 0);

	CMatrix res(dim, dim, 0);

	for (size_t row = 0; row < dim; ++row)
	{
		(res)[row][row] = 1;
	}

	return res;
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