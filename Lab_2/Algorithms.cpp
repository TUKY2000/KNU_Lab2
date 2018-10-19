#include "Algorithms.h"
#include <cmath>
#include <iostream>

CAlgorithms::CAlgorithms()
{
	matr = new CMatrix;
}


CAlgorithms::CAlgorithms(const CMatrix & _matr)
{
	matr = new CMatrix(_matr);
}

void CAlgorithms::downlMatr(const CMatrix & _matr)
{
	matr = new CMatrix(_matr);
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
			std::pair<unsigned const int, double> maxInCol = findMax(index);
			swap(maxInCol.first, next);
			std::cout << std::endl << *matr;
			normalize(next, maxInCol.second);
			std::cout << std::endl << *matr;
			subtraction(next);
			std::cout << std::endl << *matr;
				++next;
		}
	}
	normalize(next, index);

	return next;
}

std::pair<unsigned const int, double> CAlgorithms::findMax(const int & col) const
{
	size_t row = col;
	double maximum = abs((*matr)[row++][col]),
		buffer = 0;
		
	unsigned int res = 0;

	for (; row < matr->getRows(); ++row)
	{
		buffer = abs((*matr)[row][col]);
		if (maximum < buffer)	
		{
			maximum = buffer;
			res = row;
		}
	}

	return std::make_pair(res, maximum);
}	

void CAlgorithms::swap(const int & row1, const int & row2)
{
	if (row1 != row2)
	{
		double temp = 0;

		for (size_t col = 0; col < matr->getCols(); ++col)
		{
			temp = (*matr)[row1][col];
			(*matr)[row1][col] = (*matr)[row2][col];
			(*matr)[row2][col] = temp;
		}
	}
}

void CAlgorithms::normalize(unsigned const int & ROW, const int & elem)
{
	for (size_t col = 0; col < matr->getCols(); col++)
	{
		(*matr)[ROW][col] /= elem;
	}
}

void CAlgorithms::subtraction(unsigned int row)
{
	size_t col = 0;
	for (; row < matr->getRows(); ++row)
	{
		col = row;
		double koef = (*matr)[row + 1][col];
		for (; col < matr->getCols(); ++col)
		{
			(*matr)[row + 1][col] -= (*matr)[row][col] * koef;
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
				break;

			res = false;
			break;
		}
	}
	return res;
}

std::vector<double> CAlgorithms::reverseSubstitution(const unsigned int & equations)
{
	std::vector<double>res/*(equations)*/;
	
	for (int indx = matr->getCols() - 1; indx > 0; --indx)
	{
		int row = indx - 1;
		res.push_back((*matr)[row][matr->getCols()]);
		for (; row >= 0; --row)
		{
			(*matr)[row][matr->getCols()] -= (*matr)[row + 1][matr->getCols()] * ((*matr)[row][indx]);
		}
	}

	return res;
}


/*
double CAlgorithms::turnMatrix(double solution)
{
double precision = 0.000004; // than we will changed that and precision will become parametr from user
int result = 1;
int i, j, k;
int maxI, maxJ;
double max, fi;
turnMatr[matr->getCols]; // some problems here
for (i = 0; i < matr->getCols*matr->getRows; i++)
{
turnMatr[i] = matr[i]; // Fuck that shit. I'm coping matr here for first stap cause in MVS2012 alghoritm some bullshit here
/*
double matricaPoworota;
matricaPoworota = new double*[numberOfEquation];
for ( i = 0; i < numberOfEquation; i ++ ) {
matricaPoworota[i] = new double[numberOfEquation];}
*/
/*
}
double * temp;
temp = matr;
for (i = 0; i < matr->getCols; i++)
{
turnMatr[i] = matr[i]; //temp[i] = new double[matr->getCols];
}
double fault = 0.0;
for (i = 0; i < matr->getCols; i++)
{
for (j = i + 1; j < matr->getCols; j++)
{
fault = fault + *matr[i][j] * *matr[i][j];
}
}
fault = sqrt(2 * fault);
while (fault > precision) {
max = 0.0;
// Searching max.
for (i = 0; i < matr->getCols; i++)
{
for (j = i + 1; j < matr->getCols; j++)
{
if (*matr[i][j] > 0 && *matr[i][j] > max)
{
max = *matr[i][j];
maxI = i;
maxJ = j;
}
else if (*matr[i][j] < 0 && -*matr[i][j] > max)
{
max = -*matr[i][j];
maxI = i;
maxJ = j;
}
}
}
// zanylyaemo
for (i = 0; i < matr->getCols; i++)
{
for (j = 0; j < matr->getCols; j++)
{
*turnMatr[i][j] = 0;
}
*turnMatr[i][i] = 1;
}
// turn
if (*matr[maxI][maxI] == *matr[maxJ][maxJ])
{
*turnMatr[maxI][maxI] = *turnMatr[maxJ][maxJ] =
*turnMatr[maxJ][maxI] = sqrt(2.0) / 2.0;
*turnMatr[maxI][maxJ] = -sqrt(2.0) / 2.0;
}
else
{
fi = 0.5 * atan((2.0 * *matr[maxI][maxJ]) /
(*matr[maxI][maxI] - *matr[maxJ][maxJ]));
*turnMatr[maxI][maxI] = *turnMatr[maxJ][maxJ] = cos(fi);
*turnMatr[maxI][maxJ] = -sin(fi);
*turnMatr[maxJ][maxI] = sin(fi);
}
for (i = 0; i < *matr->getCols; i++)
{
for (j = 0; j < *matr->getCols; j++)
{
temp[i][j] = 0.0;
}
}
for (i = 0; i < matr->getCols; i++)
{
for (j = 0; j < matr->getCols; j++)
{
for (k = 0; k < matr->getCols; k++)
{
temp[i][j] = temp[i][j] + *turnMatr[k][i] * *matr[k][j];
}
}
}
for (i = 0; i < matr->getCols; i++)
{
for (j = 0; j < matr->getCols; j++)
{
*matr[i][j] = 0.0;
}
}
for (i = 0; i < matr->getCols; i++)
{
for (j = 0; j < matr->getCols; j++)
{
for (k = 0; k < matr->getCols; k++)
{
*matr[i][j] = *matr[i][j] +
temp[i][k] * *turnMatr[k][j];
}
}
}
fault = 0.0;
for (i = 0; i < matr->getCols; i++)
{
for (j = i + 1; j < matr->getCols; j++)
{
fault = fault + *matr[i][j] * *matr[i][j];
}
}
fault = sqrt(2 * fault);
for (i = 0; i < matr->getCols; i++)
{
for (j = 0; j < matr->getCols; j++)
{
temp[i][j] = 0.0;
}
}
for (i = 0; i < matr->getCols; i++)
{
for (j = 0; j < matr->getCols; j++)
{
for (k = 0; k < matr->getCols; k++)
{
temp[i][j] = temp[i][j] + solution[i][k] * *turnMatr[k][j];
}
}
}
for (i = 0; i < matr->getCols; i++)
{
for ( j = 0; j < matr->getCols; j++)
{
solution[i][j] = temp[i][j];
}
}
result++;
}
return result;
}


*/

bool CAlgorithms::isSymmetrical() // maybe ,mistake with parameter 
{
	bool result;
	size_t cols = matr->getCols();
	for (size_t col = 0; col < matr->getCols(); col++)
	{
		for (size_t row = col; row < matr->getRows() - col; row++)
		{
			if ((*matr)[col][row] != (*matr)[row][col])
			{
				result = false;
				// Bullshit with *
				break;
			}
		}
	}


	return result;
}