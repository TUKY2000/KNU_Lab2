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

// Jakobi

bool CAlgorithms::isSymmetrical() // maybe ,istake with parameter 
{
	bool result;
	//size_t cols = matr->getCols;
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

// Jakobi

std::vector<double> CAlgorithms::JakobiMethod()
{
	CMatrix * turnMatr = nullptr;
	std::vector<double> res;
	double precision = 0.000004; // than we will changed that and precision will become parametr from user 
	size_t row, col, k;
	size_t maxRow, maxCol;
	double max, fi;
	turnMatr[matr->getCols()]; // some problems here
	for (row = 0; row < (matr->getCols())*(matr->getRows()); row++) 
	{
		turnMatr[row] = matr[row]; // Fuck that shit. I'm coping matr here for first stap cause in MVS2012 alghoritm some bullshit here
		/*
		double** matricaPoworota;
matricaPoworota = new double*[numberOfEquation];
for ( i = 0; i < numberOfEquation; i ++ ) {
matricaPoworota[i] = new double[numberOfEquation];}
		*/

	}
	CMatrix * temp = nullptr;
	temp = new CMatrix(*matr);
	for (row = 0; row < matr->getCols(); row++) 
	{
		turnMatr[row] = matr[row]; //temp[i] = new double[matr->getCols];
	}
	double fault = 0.0;
	for (row = 0; row < matr->getCols(); row++) 
	{
		for (col = row + 1; col < matr->getCols(); col++) 
		{
			fault = fault + (*matr)[row][col] * (*matr)[row][col];
		}
	}
	fault = sqrt(2 * fault);
	while (fault > precision) {
		max = 0.0;
		// Searching max.
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = row + 1; col < matr->getCols(); col++) 
			{
				if ((*matr)[row][col] > 0 && (*matr)[row][col] > max) 
				{
					max = (*matr)[row][col];
					maxRow = row;
					maxCol = col;
				}
				else if ((*matr)[row][col] < 0 && - (*matr)[row][col] > max) 
				{
					max = -(*matr)[row][col];
					maxRow = row;
					maxCol = col;
				}
			}
		}
		// zanylyaemo
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = 0; col < matr->getCols(); col++) 
			{
				*turnMatr[row][col] = 0;
			}
			*turnMatr[row][row] = 1;
		}
		// turn 
		if ((*matr)[maxRow][maxRow] == (*matr)[maxCol][maxCol]) 
		{
			*turnMatr[maxRow][maxRow] = *turnMatr[maxCol][maxCol] =
				*turnMatr[maxCol][maxRow] = sqrt(2.0) / 2.0;
			*turnMatr[maxRow][maxCol] = -sqrt(2.0) / 2.0;
		}
		else 
		{
			fi = 0.5 * atan((2.0 * (*matr)[maxRow][maxCol]) /
				((*matr)[maxRow][maxRow] - (*matr)[maxCol][maxCol]));
			*turnMatr[maxRow][maxRow] = *turnMatr[maxCol][maxCol] = cos(fi);
			*turnMatr[maxRow][maxCol] = -sin(fi);
			*turnMatr[maxCol][maxRow] = sin(fi);
		}
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = 0; col < matr->getCols(); col++) 
			{
				*temp[row][col] = 0.0;
			}
		}
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = 0; col < matr->getCols(); col++) 
			{
				for (k = 0; k < matr->getCols(); k++) 
				{
					*temp[row][col] = *temp[row][col] + *turnMatr[k][row] * (*matr)[k][col];
				}
			}
		}
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = 0; col < matr->getCols(); col++) 
			{
				(*matr)[row][col] = 0.0;
			}
		}
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = 0; col < matr->getCols(); col++) 
			{
				for (k = 0; k < matr->getCols(); k++) 
				{
					(*matr)[row][col] = (*matr)[row][col] +
					(*temp)[row][k] * (*turnMatr)[k][col];
				}
			}
		}
		fault = 0.0;
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = row + 1; col < matr->getCols(); col++) 
			{
				fault = fault + (*matr)[row][col] * (*matr)[row][col];
			}
		}
		fault = sqrt(2 * fault);
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = 0; col < matr->getCols(); col++) 
			{
				(*temp)[row][col] = 0.0;
			}
		}
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = 0; col < matr->getCols(); col++) 
			{
				for (k = 0; k < matr->getCols(); k++) 
				{
					(*temp)[row][col] = (*temp)[row][col] + res[row] * *turnMatr[k][col]; // res[row] {k} was hear let's check out wtf is that, it can be some mistakes here.
				}
			}
		}
		// inpput solution values in array
		for (row = 0; row < matr->getCols(); row++) 
		{
			for (col = 0; col < matr->getCols(); col++) 
			{
				res.push_back((*matr)[row][col]);
			}
		}
	}
	return res;
}