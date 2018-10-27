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

void CAlgorithms::downlMatr(const int & rows, const int & cols)
{
	matr = new CMatrix(rows, cols);
	std::cin >> *matr;
}

CAlgorithms::~CAlgorithms()
{
	if (matr != nullptr)
	{
		delete matr;
		matr = nullptr;
	}
}


CMatrix CAlgorithms::GaussianElimination()
{
	unsigned int equations = directElimination();
	return reverseSubstitution(equations);
}

unsigned int CAlgorithms::directElimination()
{
	size_t index = 0;
	unsigned int next = index;
	unsigned const int iters = matr->getRows() - 1;
	std::pair<unsigned int, double> maxInCol;
	for (; index < iters; ++index)	
	{
		if (!empty(index))
		{
			maxInCol = findMax(index);
			swap(maxInCol.first, next);
			std::cout << std::endl << *matr;
			normalize(next, maxInCol.second);
			std::cout << std::endl << *matr;
			subtraction(next);
			std::cout << std::endl << *matr;
				++next;
		}
		else
		{
			throw std::logic_error("System of equations has not solution.");
		}
	}
	maxInCol = findMax(index);
	normalize(next, maxInCol.second);
	std::cout << std::endl << *matr;

	return next;
}

std::pair<unsigned const int, double> CAlgorithms::findMax(const int & col) const
{
	size_t row = col;
	unsigned int res = row;
	double maximum = (*matr)[row++][col],
		buffer = 0;
		
	

	for (; row < matr->getRows(); ++row)
	{
		buffer = (*matr)[row][col];
		if (abs(maximum) < abs(buffer))	
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

void CAlgorithms::normalize(unsigned const int & ROW, const double & elem)
{
	for (size_t col = 0; col < matr->getCols(); col++)
	{
		(*matr)[ROW][col] /= elem;
	}
}

void CAlgorithms::subtraction(unsigned int ROW)
{
	size_t col = ROW;
	for (size_t row = ROW + 1; row < matr->getRows(); ++row)
	{
		col = ROW;
		double koef = (*matr)[row][col];
		for (; col < matr->getCols(); ++col)
		{
			(*matr)[row][col] -= (*matr)[ROW][col] * koef;
		}
	}
}

bool CAlgorithms::empty(const unsigned int & row) const
{
	bool res = true;
	for (size_t col = 0; col < matr->getCols(); ++col)
	{
		if ((*matr)[row][col] != 0)
		{
			if (col == matr->getCols())
				break;

			res = false;
			break;
		}
	}
	return res;
}

CMatrix CAlgorithms::reverseSubstitution(const unsigned int & equations)
{
	CMatrix res(1, matr->getCols() - 2);
	double Ai_lead
		, koef;

	unsigned int rowLead = matr->getRows() - 1;

	for (int col = matr->getCols() - 2; col >= 0;--col)
	{ 
		Ai_lead = (*matr)[rowLead][matr->getCols() - 1];
		res[0][col] = (Ai_lead);
		for (int row = rowLead; row > 0; --row)
		{
			koef = (*matr)[row - 1][col];
			(*matr)[row - 1][matr->getCols() - 1] -= koef * Ai_lead;
			(*matr)[row - 1][col] -= koef * (*matr)[row][col];
		}
		--rowLead;
		std::cout << *matr << std::endl;
	}
	
	return res;
}


// Jacobi

std::vector<double>  CAlgorithms::JakobiMethod()
{
	CMatrix * turnMatr = nullptr;
	std::vector<double> res;
	double precision = 0.000004; // than we will changed that and precision will become parameter from user 
	size_t maxRow = matr-> getRows(), maxCol = matr ->getCols();
	double max = 0.0;
	turnMatr = new CMatrix(*matr);;
	double fault = 0.0;
	// add to while 
	for (size_t row = 0; row < matr->getCols(); row++) 
	{
		for (size_t col = row + 1; col < matr->getCols(); col++) 
		{
			fault = fault + (*matr)[row][col] * (*matr)[row][col];
		}
	}
	while (fault > precision) 
	{
		// Searching max.
		JakobiFindMax(max, maxRow, maxCol);

		// preparing matrix for turn
		prepareTurnMatr(maxRow, maxCol, *turnMatr);
		
		// turn 
		JakobiTurnMatrix(*turnMatr);
	}
	// input solution values in array
	JakobiSolution(res);

		return res;
}

// check architecture
void CAlgorithms::JakobiFindMax( double max, size_t &maxRow, size_t &maxCol)
{
		max = 0.0;
		for (size_t row = 0; row < matr->getCols(); row++)
		{
			for (size_t col = row + 1; col < matr->getCols(); col++)
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
}

// change vector to matrix 1*n
void CAlgorithms::JakobiSolution(std::vector<double> res)
{
	for (size_t  row = 0; row < matr->getCols(); row++)
	{
		for (size_t  col = 0; col < matr->getCols(); col++)
		{
			res.push_back((*matr)[row][col]);
		}
	}
}

void CAlgorithms::prepareTurnMatr(size_t maxRow, size_t maxCol, CMatrix &turnMatr)
{
	double fi;
	bool res = false;
	for (size_t row = 0; row < matr->getCols(); row++)
	{
		for (size_t col = 0; col < matr->getCols(); col++)
		{
			turnMatr[row][col] = 0;
		}
		turnMatr[row][row] = 1;
	}
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
}

void CAlgorithms::JakobiTurnMatrix( CMatrix &turnMatr)
{
	CMatrix * temp = nullptr;
	temp = new CMatrix(*matr);

	//*temp = (turnMatr) * (*matr);
	
	for (size_t row = 0; row < matr->getCols(); row++)
	{
		for (size_t col = 0; col < matr->getCols(); col++)
		{
			for (size_t k = 0; k < matr->getCols(); k++)
			{
				*temp[row][col] = *temp[row][col] + turnMatr[k][row] * (*matr)[k][col]; // пофиксить баг с вылетом
			}
		}
	}
	// change to mul matrix (both for) 
	*temp = (*matr) * (turnMatr);

	for (size_t row = 0; row < matr->getCols(); row++)
	{
		for (size_t col = 0; col < matr->getCols(); col++)
		{
			(*matr)[row][col] = 0.0;
		}
	}

	//*temp = (*matr) * (turnMatr);
	for (size_t  row = 0; row < matr->getCols(); row++)
	{
		for (size_t  col = 0; col < matr->getCols(); col++)
		{
			for (size_t k = 0; k < matr->getCols(); k++)
			{
				(*matr)[row][col] = (*matr)[row][col] +
					(*temp)[row][k] * turnMatr[k][col];
			}
		}
	}

	// Jakobi method fault
	double fault = 0.0;
	for (size_t row = 0; row < matr->getCols(); row++)
	{
		for (size_t col = row + 1; col < matr->getCols(); col++)
		{
			fault = fault + (*matr)[row][col] * (*matr)[row][col];
		}
	}
	for (size_t row = 0; row < matr->getCols(); row++)
	{
		for (size_t col = 0; col < matr->getCols(); col++)
		{
			(*temp)[row][col] = 0.0;
		}
	}
	//*temp = (turnMatr) * (turnMatr);
	for (size_t row = 0; row < matr->getCols(); row++)
	{
		for (size_t col = 0; col < matr->getCols(); col++)
		{
			for (size_t k = 0; k < matr->getCols(); k++)
			{
				(*temp)[row][col] = (*temp)[row][col] + turnMatr[k][row] * turnMatr[k][col]; // res[row][k] was hear let's check out wtf is that, it can be some mistakes here.
			}
		}
	}
	if (temp!= nullptr) delete temp;
}


double CAlgorithms::dispRow(const double && row) const
{
	double res = 0;

	for (size_t col = 0; col < matr->getCols(); col++)
	{
		res += (*matr)[row][col];
	}

	res /= matr->getCols();

	return res;
}

double CAlgorithms::dispRows(const double && row1, const double && row2) const
{
	double res = 0;

	for (size_t col = 0; col < matr->getCols(); col++)
	{
		res += (*matr)[row1][col] * (*matr)[row1][col];
	}

	res /= matr->getCols();

	return res;
}


CMatrix CAlgorithms::LinRegression() const
{
	double dispY = dispRow(1)
		, dispX = dispRow(2)
		, dispXY = dispRows(1, 2)
		, dispXX = dispRows(1, 1)

		, argA = (dispX * dispY - dispXY) / (dispX * dispX - dispXX)
		, argB = (dispXY - argA * dispXX) / dispX;

	CMatrix res(1, 2);
	res[0][0] = argA;
	res[0][1] = argB;

	return res;
}




// kachmage