//
// Created By Ivan Martsilenko and Arthur Onyshkevych
//
//
// All rights reserved
//

#include "Algorithms.h"
#include <cmath>
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>

CAlgorithms::CAlgorithms()
{
	pMatr = nullptr;
	pA = nullptr;
	pB = nullptr;
}


CAlgorithms::~CAlgorithms()
{
	if (pMatr != nullptr)
	{
		delete pMatr;
	}

	pA = nullptr;
	pB = nullptr;
}


CMatrix CAlgorithms::GaussianElimination(const CMatrix * _A, const CMatrix * _B)
{
	// prepare matrix for working
	if (pA != nullptr) { delete pA; }			
	pA = _A;
	if (pB != nullptr) { delete pB; }			
	pB = _B;
	if (pMatr != nullptr) { delete pMatr; }		
	pMatr = (*pA) | (*pB);
 	
	directElimination();
	CMatrix * res = &reverseSubstitution();
	checkSolution(res);
	return *res;
}

bool CAlgorithms::nonZeroInCol(const int & col, std::pair<unsigned int, double> & leadEl) const
{
	for (size_t row = col; row < pMatr->getRows(); row++)
	{
		if ((*pMatr)[row][col] != 0)
		{
			leadEl = std::make_pair(row, (*pMatr)[row][col]);
			return true;
		}
	}
	return false;
}

void CAlgorithms::directElimination()
{
	unsigned int  index = 0
		, next = index
		, emptLines = 0;

	std::pair<unsigned int, double> leadEl;

	for (; index < pMatr->getRows(); ++index)
	{
		if (!empty(index))
		{
			if (nonZeroInCol(index, leadEl))
			{
				swap(leadEl.first, next);
				normalize(next, leadEl.second);
				subtraction(next);
				++next;
			}
			else
			{
				throw std::logic_error("System of equations has an infinite number of solutions.");
			}
		}
		else
		{
			if ((*pMatr)[index][pMatr->getCols()] != 0)
			{
				throw std::logic_error("System of equations has not solution.");
			}
			else if (pMatr->getRows() + emptLines < pMatr->getCols())
			{
				throw std::logic_error("System of equations has an infinite number of solutions: SoE has " + std::to_string(emptLines) + " or more linearly dependent equations");
			}
			else
			{
				++emptLines;
			}
		}
	}
}

std::pair<unsigned const int, double> CAlgorithms::findMax(const int & col) const
{

	size_t row = col;
	unsigned int res = row;
	double maximum = (*pMatr)[row++][col],
		buffer = 0;



	for (; row < pMatr->getRows(); ++row)
	{
		buffer = (*pMatr)[row][col];
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

		for (size_t col = 0; col < pMatr->getCols(); ++col)
		{
			temp = (*pMatr)[row1][col];
			(*pMatr)[row1][col] = (*pMatr)[row2][col];
			(*pMatr)[row2][col] = temp;
		}
	}
}

void CAlgorithms::normalize(unsigned const int & ROW, const double & elem)
{
	for (size_t col = 0; col < pMatr->getCols(); col++)
	{
		(*pMatr)[ROW][col] /= elem;
	}
}

void CAlgorithms::subtraction(unsigned int ROW)
{
	if (ROW < pMatr->getRows() - 1)
	{
		size_t col = ROW;
		for (size_t row = ROW + 1; row < pMatr->getRows(); ++row)
		{
			col = ROW;
			double koef = (*pMatr)[row][col];
			for (; col < pMatr->getCols(); ++col)
			{
				(*pMatr)[row][col] -= (*pMatr)[ROW][col] * koef;
			}
		}
	}
}

bool CAlgorithms::empty(const unsigned int & row) const
{
	bool res = true;
	for (size_t col = 0; col < pMatr->getCols(); ++col)
	{
		if ((*pMatr)[row][col] != 0)
		{
			if (col == pMatr->getCols())
				break;

			res = false;
			break;
		}
	}
	return res;
}

CMatrix & CAlgorithms::reverseSubstitution()
{
	CMatrix *res = new CMatrix(1, pMatr->getCols() - 1);
	double Ai_lead
		, koef;

	int rowLead = pMatr->getRows() - 1;

	for (int col = pMatr->getCols() - 2; col >= 0; --col)
	{
		Ai_lead = (*pMatr)[rowLead][pMatr->getCols() - 1];
		(*res)[0][col] = (Ai_lead);
		for (int row = rowLead; row > 0; --row)
		{
			koef = (*pMatr)[row - 1][col];
			(*pMatr)[row - 1][pMatr->getCols() - 1] -= koef * Ai_lead;
			(*pMatr)[row - 1][col] -= koef * (*pMatr)[rowLead][col];
		}
		--rowLead;
	}

	return *res;
}


// Jacobi

CMatrix CAlgorithms::JakobiMethod(const CMatrix * _Symetrical)
{
	pMatr = new CMatrix(*_Symetrical);

	//std::cout << *pMatr << "\n";
	CMatrix * turnMatr = nullptr;
	turnMatr = new CMatrix(*pMatr);
	double precision = 0.005; // than we will changed that and precision will become parameter from user 
	size_t maxRow = pMatr->getRows(), maxCol = pMatr->getCols();
	double max = 0.0;
	double fault = 0.0;
	calculateJakobiFault(fault);
	int i = 1;
	while (fault > precision)
	{
		max = 0.0;
		// Searching max element.
		JakobiFindMax(max, maxRow, maxCol);
		if (max < precision) break; // need to end while if Jacobi Method finished? but fault still bigger than precision
		prepareTurnMatr(maxRow, maxCol, *turnMatr);
		JakobiTurnMatrix(*turnMatr);
		cleanZeroElements(precision);
		calculateJakobiFault(fault);
	}
	CMatrix * res = nullptr;
	res = &JakobiSolution();
	return *res;
}

void CAlgorithms::JakobiFindMax(double &max, size_t &maxRow, size_t &maxCol)
{

	for (size_t row = 0; row < pMatr->getCols(); row++)
	{
		for (size_t col = 0; col < pMatr->getCols(); col++)
		{
			if (row != col)
			{
				if ((*pMatr)[row][col] > 0 && (*pMatr)[row][col] > max)
				{
					max = (*pMatr)[row][col];
					maxRow = row;
					maxCol = col;
				}
				else if ((*pMatr)[row][col] < 0 && -(*pMatr)[row][col] > max)
				{
					max = -(*pMatr)[row][col];
					maxRow = row;
					maxCol = col;
				}
			}
		}
	}
}

CMatrix & CAlgorithms::JakobiSolution()
{
	CMatrix * res = new CMatrix(1, pMatr->getCols(), 0);
	for (size_t row = 0; row < res->getCols(); row++)
	{
		(*res)[0][row] = (*pMatr)[row][row];
	}

	return *res;
}

void CAlgorithms::makeIdentityMatrix(CMatrix & turnMatr)
{
	for (size_t row = 0; row < pMatr->getCols(); row++)
	{
		for (size_t col = 0; col < pMatr->getCols(); col++)
		{
			turnMatr[row][col] = 0;
		}
		turnMatr[row][row] = 1;
	}
}

void CAlgorithms::makeZeroMatrix(CMatrix & other)
{
	for (size_t row = 0; row < other.getCols(); row++)
	{
		for (size_t col = 0; col < other.getCols(); col++)
		{
			(other)[row][col] = 0.0;
		}
	}
}

void CAlgorithms::prepareTurnMatr(size_t maxRow, size_t maxCol, CMatrix &turnMatr)
{
	double fi;
	makeIdentityMatrix(turnMatr);

	if (((*pMatr)[maxRow][maxRow] == (*pMatr)[maxCol][maxCol]) && ((*pMatr)[maxCol][maxCol] == (*pMatr)[maxRow][maxCol]))
	{
		turnMatr[maxRow][maxRow] = turnMatr[maxCol][maxCol] =
			turnMatr[maxCol][maxRow] = sqrt(2.0) / 2.0;
		turnMatr[maxRow][maxCol] = -sqrt(2.0) / 2.0;
	}
	else
	{
		fi = 0.5 * atan((2.0 * (*pMatr)[maxRow][maxCol]) /
			((*pMatr)[maxRow][maxRow] - (*pMatr)[maxCol][maxCol]));
		turnMatr[maxRow][maxRow] = turnMatr[maxCol][maxCol] = cos(fi);
		turnMatr[maxRow][maxCol] = -sin(fi);
		turnMatr[maxCol][maxRow] = sin(fi);
	}
}

void CAlgorithms::JakobiTurnMatrix(CMatrix &turnMatr)
{
	CMatrix * temp = nullptr;
	temp = new CMatrix(*pMatr);

	*temp = (~turnMatr) * (*pMatr);

	*temp = (*temp) * (turnMatr);

	double fault = 0.0;
	*pMatr = *temp;
	if (temp != nullptr) delete temp;
}


void CAlgorithms::calculateJakobiFault(double & fault)
{
	for (size_t row = 0; row < pMatr->getCols(); row++)
	{
		for (size_t col = row + 1; col < pMatr->getCols(); col++)
		{
			fault = fault + (*pMatr)[row][col] * (*pMatr)[row][col];
		}
	}
	fault = sqrt(fault);
}

void CAlgorithms::cleanZeroElements(double precision)
{
	for (size_t row = 0; row < pMatr->getCols(); row++)
	{
		for (size_t col = 0; col < pMatr->getCols(); col++)
		{
			if ((*pMatr)[row][col] < precision) (*pMatr)[row][col] = 0;
		}
	}

}

// Linear regression
CMatrix & CAlgorithms::getFreeMembMatr(const CMatrix & pointers)
{
	CMatrix * res = nullptr;
	res = new CMatrix(pointers.getCols(), 1, 0);

	//	first elem
	for (size_t row = 0; row < pointers.getRows(); ++row)
	{
		(*res)[0][0] += (pointers)[row][0];

	}

	//	 from 1 to last elems
	for (size_t col = 1, row = 1; col < pointers.getCols(); ++col, ++row)
	{
		for (size_t rowAdd = 0; rowAdd < pointers.getRows(); ++rowAdd)
		{
			(*res)[row][0] += (pointers)[rowAdd][0] * (pointers)[rowAdd][col];
		}
	}

	return *res;
}

CMatrix & CAlgorithms::getSumMatr(const CMatrix & pointers)
{
	CMatrix * res = nullptr;
	res = new CMatrix(pointers.getCols(), pointers.getCols(), 0);

	// [0][0] elem
	*res[0][0] = pointers.getRows();

	double summ = 0;

	// 0 row and 0 col
	for (size_t col = 1; col < pointers.getCols(); ++col)
	{
		for (size_t row = 0; row < pointers.getRows(); ++row)
		{
			summ += (pointers)[row][col];
		}

		(*res)[col][0] = (*res)[0][col] = summ;
		summ = 0;
	}

	// from 1 to N
	for (size_t row = 1; row < res->getRows(); ++row)
	{
		for (size_t col = 1; col < res->getRows(); ++col)
		{
			//	calculate number of element of result matrix [row][col]
			for (size_t dot = 0; dot < pointers.getRows(); ++dot)
			{
				(*res)[row][col] += (pointers)[dot][row] * (pointers)[dot][col];
			}
		}
	}
	return *res;
}


CMatrix CAlgorithms::LinRegression(const CMatrix * _Pointers)
{
	CMatrix A = getSumMatr(*_Pointers);
 	CMatrix B = getFreeMembMatr(*_Pointers);
	
	std::cout << std::endl << std::endl << A << std::endl << std::endl << B << std::endl << std::endl;

	return GaussianElimination(&A, &B);
}

// kachmage
CMatrix CAlgorithms::KachmageMethod(const CMatrix * _A, const CMatrix * _B)
{
	// prepare matrix for working
	if (pA != nullptr) { delete pA; }			pA = _A;
	if (pB != nullptr) { delete pB; }			pB = _B;
	if (pMatr != nullptr) { delete pMatr; }		pMatr = (*pA | *pB);

	double precision = 0.00000001;

	CMatrix X_i = getMRow(0)
		, X_prev
		, M_row;


	unsigned int row = 0;

	double check = 0;
	do
	{
		M_row = getMRow(row);

		X_prev = X_i;

		X_i = X_i + M_row * (((*pMatr)[row][pMatr->getCols() - 1] - skalar(M_row, X_i)) / (norma(M_row) * norma(M_row)));

		check = norma(X_i - X_prev);

		std::cout << row << '\t' << M_row << '\t' << X_i << std::endl;

		++row;

		if (row >= pMatr->getRows())	row = 0;
		
	} while (check >= precision);


	checkSolution(&X_i);

	return X_i;
}

double CAlgorithms::norma(const CMatrix & vect)
{
	double squareSumm = 0;
	for (unsigned int col = 0; col < vect.getCols(); ++col)
	{
		squareSumm += vect[0][col] * vect[0][col];
	}

	return sqrt(squareSumm);
}

CMatrix CAlgorithms::getMRow(const unsigned int & row)
{
	CMatrix res(1, pMatr->getCols() - 1);
	double val = 0;	//	time val for testing
	for (unsigned int col = 0; col < res.getCols(); ++col)
	{
		val = (*pMatr)[row][col];
		(res)[0][col] = val;
	}
	return res;
}

double CAlgorithms::skalar(const CMatrix & A, const CMatrix & B)
{
	if (A.getCols() != B.getCols()) throw std::logic_error("");

	double res = 0
		, val1 = 0
		, val2 = 0;

	for (unsigned int i = 0; i < A.getCols(); ++i)
	{
		val1 = A[0][i];
		val2 = B[0][i];
		res += val1 * val2;
	}
	return res;
}

void CAlgorithms::checkSolution(CMatrix * result)
{
	CMatrix transport = ~(*result);
	CMatrix Ax = (CMatrix)(*pA) * transport;
	CMatrix res = Ax - *pB;
	CMatrix res_transp = ~res;
	std::cout << "check : " << res_transp;
}