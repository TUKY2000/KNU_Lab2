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
/*
double CAlgorithms::turnMatrix(double **solution)
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
		double** matricaPoworota;
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