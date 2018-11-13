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
	matr = new CMatrix;
	original = new CMatrix(*matr);
}


CAlgorithms::CAlgorithms(const CMatrix & _matr)
{
	matr = new CMatrix(_matr);
	original = new CMatrix(*matr);
}

void CAlgorithms::downlMatr(const CMatrix & _matr)
{
	matr = new CMatrix(_matr);
	original = new CMatrix(*matr);
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


CMatrix & CAlgorithms::GaussianElimination()
{
	directElimination();
	CMatrix * res = new CMatrix(reverseSubstitution());
	checkSolution(*res);
	return *res;
}

bool CAlgorithms::nonZeroInCol(const int & col, std::pair<unsigned int, double> & leadEl) const
{
	for (size_t row = col; row < matr->getRows(); row++)
	{
		if ((*matr)[row][col] != 0)
		{
			leadEl = std::make_pair(row, (*matr)[row][col]);
			return true;
		}
	}
	return false;
}

unsigned int CAlgorithms::directElimination()
{
	unsigned int  index = 0
		, next = index
		, emptLines = 0;

	std::pair<unsigned int, double> leadEl;

	for (; index < matr->getRows(); ++index)
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
			if ((*matr)[index][matr->getCols()] != 0)
			{
				throw std::logic_error("System of equations has not solution.");
			}
			else if (matr->getRows() + emptLines < matr->getCols())
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
	if (ROW < matr->getRows() - 1)
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
}

bool CAlgorithms::empty(const unsigned int & row) const
{
	bool res = true;
	for (int col = 0; col < matr->getCols(); ++col)
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

CMatrix & CAlgorithms::reverseSubstitution()
{
	CMatrix *res = new CMatrix(1, matr->getCols() - 1);
	double Ai_lead
		, koef;

	int rowLead = matr->getRows() - 1;

	for (int col = matr->getCols() - 2; col >= 0; --col)
	{
		Ai_lead = (*matr)[rowLead][matr->getCols() - 1];
		(*res)[0][col] = (Ai_lead);
		for (int row = rowLead; row > 0; --row)
		{
			koef = (*matr)[row - 1][col];
			(*matr)[row - 1][matr->getCols() - 1] -= koef * Ai_lead;
			(*matr)[row - 1][col] -= koef * (*matr)[rowLead][col];
		}
		--rowLead;
	}

	return *res;
}


// Jacobi

CMatrix &   CAlgorithms::JakobiMethod()
{
	std::cout << *matr << "\n";
	CMatrix * turnMatr = nullptr;
	turnMatr = new CMatrix(*matr);
	double precision = 0.005; // than we will changed that and precision will become parameter from user 
	size_t maxRow = matr->getRows(), maxCol = matr->getCols();
	double max = 0.0;
	double fault = 0.0;
	calculateJakobiFault(fault);
	int i = 1;
	while (fault > precision)
	{
		max = 0.0;
		// Searching max element.
		JakobiFindMax(max, maxRow, maxCol);
		if (max < precision) break; // need to end while if Jakobi Method finished? but fault still bigger than precision
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

	for (int row = 0; row < matr->getCols(); row++)
	{
		for (int col = 0; col < matr->getCols(); col++)
		{
			if (row != col)
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
}

CMatrix & CAlgorithms::JakobiSolution()
{
	CMatrix * res = new CMatrix(1, matr->getCols(), 0);
	for (int row = 0; row < res->getCols(); row++)
	{
		(*res)[0][row] = (*matr)[row][row];
	}

	return *res;
}

void CAlgorithms::makeIdentityMatrix(CMatrix & turnMatr)
{
	for (int row = 0; row < matr->getCols(); row++)
	{
		for (int col = 0; col < matr->getCols(); col++)
		{
			turnMatr[row][col] = 0;
		}
		turnMatr[row][row] = 1;
	}
}

void CAlgorithms::makeZeroMatrix(CMatrix & other)
{
	for (int row = 0; row < other.getCols(); row++)
	{
		for (int col = 0; col < other.getCols(); col++)
		{
			(other)[row][col] = 0.0;
		}
	}
}

void CAlgorithms::prepareTurnMatr(size_t maxRow, size_t maxCol, CMatrix &turnMatr)
{
	double fi;
	makeIdentityMatrix(turnMatr);

	if (((*matr)[maxRow][maxRow] == (*matr)[maxCol][maxCol]) && ((*matr)[maxCol][maxCol] == (*matr)[maxRow][maxCol]))
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

void CAlgorithms::JakobiTurnMatrix(CMatrix &turnMatr)
{
	CMatrix * temp = nullptr;
	temp = new CMatrix(*matr);

	*temp = (~turnMatr) * (*matr);

	*temp = (*temp) * (turnMatr);

	double fault = 0.0;
	*matr = *temp;
	if (temp != nullptr) delete temp;
}


void CAlgorithms::calculateJakobiFault(double & fault)
{
	for (int row = 0; row < matr->getCols(); row++)
	{
		for (int col = row + 1; col < matr->getCols(); col++)
		{
			fault = fault + (*matr)[row][col] * (*matr)[row][col];
		}
	}
	fault = sqrt(fault);
}

void CAlgorithms::cleanZeroElements(double precision)
{
	for (int row = 0; row < matr->getCols(); row++)
	{
		for (int col = 0; col < matr->getCols(); col++)
		{
			if ((*matr)[row][col] < precision) (*matr)[row][col] = 0;
		}
	}

}

// Linear regression
CMatrix & CAlgorithms::getFreeMembMatr()
{
	CMatrix * res = nullptr;
	res = new CMatrix(matr->getCols(), 1, 0);

	//	first elem
	for (size_t row = 0; row < matr->getRows(); ++row)
	{
		(*res)[0][0] += (*matr)[row][0];

	}

	//	 from 1 to last elems
	for (size_t col = 1, row = 1; col < matr->getCols(); ++col, ++row)
	{
		for (size_t rowAdd = 0; rowAdd < matr->getRows(); ++rowAdd)
		{
			(*res)[row][0] += (*matr)[rowAdd][0] * (*matr)[rowAdd][col];
		}
	}

	return *res;
}

CMatrix & CAlgorithms::getSumMatr()
{
	CMatrix * res = nullptr;
	res = new CMatrix(matr->getCols(), matr->getCols(), 0);

	// [0][0] elem
	*res[0][0] = matr->getRows();

	double summ = 0;

	// 0 row and 0 col
	for (int col = 1; col < matr->getCols(); ++col)
	{
		for (int row = 0; row < matr->getRows(); ++row)
		{
			summ += (*matr)[row][col];
		}

		(*res)[col][0] = (*res)[0][col] = summ;
		summ = 0;
	}

	// from 1 to N
	for (int row = 1; row < res->getRows(); ++row)
	{
		for (int col = 1; col < res->getRows(); ++col)
		{
			//	calculate number of element of result matrix [row][col]
			for (int dot = 0; dot < matr->getRows(); ++dot)
			{
				(*res)[row][col] += (*matr)[dot][row] * (*matr)[dot][col];
				
			}
		}
	}
	return *res;
}


CMatrix & CAlgorithms::LinRegression()
{
	CMatrix * res = new CMatrix;

	CMatrix *A = nullptr;
	CMatrix *B = nullptr;

	A = &getSumMatr();
	B = &getFreeMembMatr();
	
	if (matr != nullptr)	delete matr;
	matr = &((*A) | (*B));

	if (original != nullptr)	delete original;
	original = new CMatrix(*matr);

	std::cout << *matr;
	*res = GaussianElimination();
	return *res;
}

// kachmage
CMatrix & CAlgorithms::KachmageMethod()
{
	double precision = 0.000000001;

	CMatrix * X_i = new CMatrix(1, matr->getCols() - 1)
		, *X_prev = new CMatrix(1, matr->getCols() - 1)
		, *M_row = new CMatrix(1, matr->getCols() - 1)
		, *Sub = nullptr
		, *Mult = nullptr
		, *Temp = nullptr;

	if (X_i != nullptr) delete X_i;
	X_i = &getMRow(0);

	*X_prev = *X_i;

	unsigned int row = 0;

	double skalarVal = 0
		, freeVal = 0
		, numerator = 0
		, denominator = 0
		, fraction = 0
		, check = 0;
	do
	{
		if (M_row != nullptr)	delete M_row;
		M_row = &getMRow(row);

		skalarVal = skalar(*M_row, *X_i);
		freeVal = (*matr)[row][matr->getCols() - 1];
		numerator = freeVal - skalarVal;
		denominator = (norma(*M_row) * norma(*M_row));
		fraction = (numerator) / denominator;

		if (X_prev != nullptr)	delete X_prev;
		X_prev = new CMatrix(*X_i);

		if (Mult != nullptr) delete Mult;
		Mult = &(*M_row * (fraction));
		
		if (Temp != nullptr) delete Temp;
		Temp = &(*X_i + *Mult);

		if (X_i != nullptr) delete X_i;
		X_i = new CMatrix(*Temp);

		if (Sub != nullptr) delete Sub;
		Sub = &(*X_i - *X_prev);

		check = norma(*Sub);

		std::cout << row << '\t' << *M_row << '\t' << *X_i << std::endl;

		++row;

		if (row >= matr->getRows())	row = 0;
		
	} while (check >= precision);


	if (M_row != nullptr)	delete M_row;
	if (X_prev != nullptr)	delete X_prev;

	checkSolution(*X_i);

	return *X_i;
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

CMatrix & CAlgorithms::getMRow(const unsigned int & row)
{
	CMatrix * res = new CMatrix(1, matr->getCols() - 1);
	double val = 0;	//	time val for testing
	for (unsigned int col = 0; col < res->getCols(); ++col)
	{
		val = (*matr)[row][col];
		(*res)[0][col] = val;
	}
	return *res;
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

void CAlgorithms::checkSolution(const CMatrix & result)
{
	double num = 0
		, num1 = 0
		, num2 = 0;

	std::cout << std::endl << "Checking solution of SoLE: " << std::endl;
	for (size_t row = 0; row < original->getRows(); ++row)
	{
		for (size_t col = 0; col < original->getCols() - 1; ++col)
		{
			num1 = (*original)[row][col];
			num2 = result[0][col];
			num += num1 * num2;
		}
		std::cout << num << ", ";
		num = 0;
	}
}

// kachmage
//double CAlgorithms::KachmageMethod(CMatrix & b)
//{
	//double precision = 0.00000000001;
	//CMatrix x(*this, 0);
	//CMatrix x1(1, N_size, 0);
	//CMatrix sub(1, N_size, 1);
	//int j = 0;
	//while (sub.norma() > precision)
	//{
	//	CMatrix ai(*this, j);
	//	double temp = ((b.M[0][j] - ai.skal_dob(x)) / (ai.norma()*ai.norma()));
	//	ai = ai * temp;
	//	x1 = x + ai;
	//	sub = x1 - x;
	//	//  cout << sub.norma()<<endl;
	//	x = x1;
	//	if (j < N_size - 1)
	//		j++;
	//	else j = 0;
	//}
	//return x;
//}