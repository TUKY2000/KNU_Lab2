#pragma once

#include "Matrix.h"
#include <vector>

class CAlgorithms
{
public:
	CAlgorithms();
	~CAlgorithms();

	void SoLEtoMATR(const std::istream & input);

	std::vector<double> GaussianElimination();

private:

	CMatrix * matr = nullptr;
	std::vector<double> Ai;

	unsigned int directElimination();
	int findMax(const int & col) const;
	void swap(const int & row1, const int & row2);
	void normalize(const int & elrow, const int & elcol);
	void subtraction(unsigned int row);

	bool empty(const unsigned int & row) const;

	std::vector<double> reverseSubstitution(const unsigned int & equations);
};

