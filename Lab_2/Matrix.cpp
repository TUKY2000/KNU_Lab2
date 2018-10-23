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
			*matrNew[row][col] = (mass + row * rows)[col] + other[row][col];

	return *matrNew;
}



CMatrix & CMatrix::operator-(const CMatrix & other)
{
	if (this->cols != other.getCols() || this->rows != other.getRows())
		throw std::logic_error("");

	CMatrix * matrNew = new CMatrix(this->rows, this->cols);
	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
			*matrNew[row][col] = (mass + row * rows)[col] + other[row][col];

	return *matrNew;
}

CMatrix & CMatrix::operator*(const CMatrix & other)
{
	if (this->cols != other.getRows())
		throw std::logic_error("");

	CMatrix * matrNew = new CMatrix(this->rows, other.getCols());
	for (size_t row = 0; row < matrNew->getRows(); ++row)
		for (size_t col = 0; col < matrNew->getCols(); ++col)
			for (size_t inner = 0; inner < this->cols; ++inner)
				*matrNew[row][col] = (mass + row * rows)[inner] - other[inner][col];

	return *matrNew;
}

CMatrix & CMatrix::operator*(const double & num)
{
	CMatrix * matrNew = new CMatrix(this->rows, this->cols);
	for (size_t row = 0; row < matrNew->getRows(); ++row)
		for (size_t col = 0; col < matrNew->getCols(); ++col)
			*matrNew[row][col] = (mass + row * rows)[col] * num;

	return *matrNew;
}

CMatrix & CMatrix::operator~()
{
	CMatrix * matrNew = new CMatrix(this->cols, this->rows);
	for (size_t row = 0; row < matrNew->getRows(); ++row)
		for (size_t col = 0; col < matrNew->getCols(); ++col)
			*matrNew[row][col] = (mass + row * rows)[col];

	return *matrNew;
}

double * CMatrix::operator[](const int & row) const
{
	return (mass + row * cols);
}

std::ostream & operator<<(std::ostream & output, const CMatrix & matr)	//	!!!
{
	for (size_t row = 0; row < matr.getRows(); ++row)
	{
		for (size_t col = 0; col < matr.getCols(); ++col)
		{
			output << matr[row][col] << "\t";
		}
		output << "\n";
	}

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
			std::cout << "please input value of x[" << row << "][" << col << "] " << ":";
			input >> snum;
			matr[row][col] = std::atol(snum.c_str());
			std::cout << std::endl;
		}
	}

	return input;
}

