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
				break;
			}
		}
	}


	return result;
}

// Jakobi

bool CAlgorithms::JakobiMethod()
{
	bool JakobiMethod = false;
	CMatrix * turnMatr = nullptr;
	std::vector<double> res;
	double precision = 0.000004; // than we will changed that and precision will become parametr from user 
	size_t row, col;
	size_t maxRow = matr-> getRows(), maxCol = matr ->getCols();
	double max = 0.0;
	turnMatr = new CMatrix(*matr);;
	double fault = 0.0;
	for (row = 0; row < matr->getCols(); row++) 
	{
		for (col = row + 1; col < matr->getCols(); col++) 
		{
			fault = fault + (*matr)[row][col] * (*matr)[row][col];
		}
	}
	fault = sqrt(2 * fault);
	while (fault > precision) 
	{
		// Searching max.
		if (!JakobiFindMax(max, col, row, maxRow, maxCol))
		{
			// throw
			return JakobiMethod;
			break;
		}
	
		// zanylyaemo
		if (!turnMatrToNull(row, col, *turnMatr))
		{
			// throw
			return JakobiMethod;
			break;
		}
		
		// turn 
		if (!JakobiTurnMatrix( row, col, maxRow, maxCol, *turnMatr))
		{
			// throw
			return JakobiMethod;
			break;
		}

		// inpput solution values in array
		if (!JakobiSolution(res, row, col))
		{
			// throw
			return JakobiMethod;
			break;
		}
	}
	
	// cout << JakobiSolution(); // res vector
	JakobiMethod = true;
	return JakobiMethod;
}

bool CAlgorithms::JakobiFindMax( double max, size_t col, size_t row, size_t maxRow, size_t maxCol)
{
	bool JakobiFindMax = false;
		max = 0.0;
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
				else if ((*matr)[row][col] < 0 && -(*matr)[row][col] > max)
				{
					max = -(*matr)[row][col];
					maxRow = row;
					maxCol = col;
				}
			}
		}

		JakobiFindMax = true;

	return JakobiFindMax;
}

bool CAlgorithms::JakobiSolution(std::vector<double> res, size_t row, size_t col)
{
	bool JakobiSolution = false;
	for (row = 0; row < matr->getCols(); row++)
	{
		for (col = 0; col < matr->getCols(); col++)
		{
			res.push_back((*matr)[row][col]);
		}
	}
	JakobiSolution = true;
	return JakobiSolution;
}

bool CAlgorithms::turnMatrToNull(size_t row, size_t col, CMatrix &turnMatr)
{
	bool res = false;
	for (row = 0; row < matr->getCols(); row++)
	{
		for (col = 0; col < matr->getCols(); col++)
		{
			turnMatr[row][col] = 0;
		}
		turnMatr[row][row] = 1;
	}
	return true;
}

bool CAlgorithms::JakobiTurnMatrix(size_t row, size_t col, size_t maxRow, size_t maxCol, CMatrix &turnMatr)
{
	bool JakobiTurnMatrix = false;
	double fi;
	CMatrix * temp = nullptr;
	temp = new CMatrix(*matr);
	if ((*matr)[maxRow][maxRow] == (*matr)[maxCol][maxCol])
	{
		turnMatr[maxRow][maxRow] = turnMatr[maxCol][maxCol] =
			turnMatr[maxCol][maxRow] = sqrt(2.0) / 2.0;
		turnMatr[maxRow][maxCol] = -sqrt(2.0) / 2.0;
	}
	else
	{
		fi = 0.5 * atan((2.0 * (*matr)[maxRow][maxCol]) /
			((*matr)[maxRow][maxRow] - (*matr)[maxCol][maxCol]));
		turnMatr[maxRow][maxRow] = turnMatr[maxCol][maxCol] = cos(fi);
		turnMatr[maxRow][maxCol] = -sin(fi);
		turnMatr[maxCol][maxRow] = sin(fi);
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
			for (size_t k = 0; k < matr->getCols(); k++)
			{
				*temp[row][col] = *temp[row][col] + turnMatr[k][row] * (*matr)[k][col];
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
			for (size_t k = 0; k < matr->getCols(); k++)
			{
				(*matr)[row][col] = (*matr)[row][col] +
					(*temp)[row][k] * turnMatr[k][col];
			}
		}
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
			for (size_t k = 0; k < matr->getCols(); k++)
			{
				(*temp)[row][col] = (*temp)[row][col] + turnMatr[k][row] * turnMatr[k][col]; // res[row][k] was hear let's check out wtf is that, it can be some mistakes here.
			}
		}
	}
	if (temp!= nullptr) delete temp;
	JakobiTurnMatrix = true;
	return JakobiTurnMatrix;
}
