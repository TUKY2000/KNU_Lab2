#include "Algorithms.h"



CAlgorithms::CAlgorithms()
{
	matr = new CMatrix;
}


CAlgorithms::~CAlgorithms()
{
	if (matr != nullptr)
	{
		delete matr;
		matr = nullptr;
	}
}


std::vector<double> CAlgorithms::GaussianElimination()
{
	unsigned int equations = directElimination();
	return reverseSubstitution(equations);
}

unsigned int CAlgorithms::directElimination()
{
	size_t index = 0;
	unsigned int next = index;
	for (; index < matr->getRows(); ++index)
	{
		if (!empty(index))
		{
			swap(findMax(index), next);
			normalize(next, index);
			subtraction(next);
			++next;
		}
	}
	normalize(next, index);

	return next;
}

int CAlgorithms::findMax(const int & col) const
{
	size_t row = 0;
	double res = *matr[row++][col];
	for (; row < matr->getRows(); ++row)
	{
		if (res < abs(*matr[row][col]))
			res = *matr[row][col];
	}

	return row;
}

void CAlgorithms::swap(const int & row1, const int & row2)
{
	if (row1 != row2)
	{
		double * temp = nullptr;
		temp = new double[matr->getCols()];

		for (size_t col = 0; col < matr->getCols(); ++col)
		{
			temp[col] = *matr[row1][col];
			*matr[row1][col] = *matr[row2][col];
			*matr[row2][col] = temp[col];
		}

		if (temp != nullptr)
		{
			delete temp;
			temp = nullptr;
		}
	}
}

void CAlgorithms::normalize(const int & elrow, const int & elcol)
{
	double koef = *matr[elrow][elcol];
	for (size_t row = elrow; row < matr->getRows(); ++row)
	{
		for (size_t col = 0; col < matr->getCols(); col++)
		{
			*matr[row][col] /= koef;
		}
	}
}

void CAlgorithms::subtraction(unsigned int row)
{
	for (; row < matr->getRows(); ++row)
	{
		for (size_t col = 0; col < matr->getCols(); ++col)
		{
			*matr[row + 1][col] -= *matr[row][col];
		}
	}
}

bool CAlgorithms::empty(const unsigned int & row) const
{
	bool res = true;
	for (size_t col = 0; col < matr->getCols(); ++col)
	{
		if (matr[row][col] != 0)
		{
			if (col == matr->getCols()) 
				throw std::logic_error("SoE is not	lineal");

			res = false;
			break;
		}
	}
	return res;
}	

std::vector<double> CAlgorithms::reverseSubstitution(const unsigned int & equations)
{
	std::vector<double>res(equations);

	for (size_t indx = matr->getCols() - 1, row = equations; indx >= 0; --indx, --row)
	{
		res[indx] = *matr[row][matr->getCols()];
		for (size_t row = indx - 1; row >= 0; --row)
		{
			*matr[row][matr->getCols()] -= *matr[row + 1][matr->getCols()] * (*matr[row][indx]);
		}
	}
	
	return res;
}

