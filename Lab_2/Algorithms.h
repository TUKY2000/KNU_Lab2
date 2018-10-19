#pragma once

#include "Matrix.h"
#include <vector>

class CAlgorithms
{
public:
	CAlgorithms();
	~CAlgorithms();

	//void SoLEtoMATR(const std::istream & input);

	//************************************
	// Function:	solve the matrix by Gaussian method
	// Returns:		vector   
	// Parameter:	void
	//************************************
	std::vector<double> GaussianElimination();



private:

	CMatrix * turnMatr = nullptr; // I need that for Jakobi. Ivan . 

	CMatrix * matr = nullptr;
	//	std::vector<double> Ai;

	//************************************
	// Function:	reduce the matrix to triangular shape (first part of Gaussian method)
	// Returns:		number of linearly independent equations  
	// Parameter:	void
	//************************************
	unsigned int directElimination();

	//************************************
	// Function:	Find max element in column
	// Returns:		number of row where is max element
	// Parameter:	const int & col
	//************************************
	int findMax(const int & col) const;

	//************************************
	// Function:	swap rows int matrix
	// Returns:		void
	// Parameter:	number of rows, which will be swapped
	//************************************
	void swap(const int & row1, const int & row2);

	//************************************
	// Function:	divide all elements in a row on by the leading element
	// Returns:		void
	// Parameter:	number of row of the leading element, number of col of the leading element
	//************************************
	void normalize(const int & elrow, const int & elcol);

	//************************************
	// Function:	nullifier all elements below in column of the leading element by subtraction of rows
	// Returns:		void
	// Parameter:	number of row of the leading element
	//************************************
	void subtraction(unsigned int row);

	//************************************
	// Function:	check if all elements in the row are null
	// Returns:		true if all elems are null, false if not
	// Parameter:	number of row 
	//************************************
	bool empty(const unsigned int & row) const;

	//************************************
	// Function:	find a vector of free members (second part of Gaussian method)
	// Returns:		vector of free members
	// Parameter:	number linearly independent equations  
	//************************************
	std::vector<double> reverseSubstitution(const unsigned int & equations);



// Jakobi  part


	
	//************************************
	// Function:	Checking if matrix is a symmetrical
	// Returns:		bool value
	// Parameter:	 double array (all matrix value)  
	//************************************
	bool isSymmetrical();		// break inside that function let's check + troubles with *

	//************************************
	// Function:	Checking if matrix is a symmetrical
	// Returns:		return new massive of own values !!!!! will change that !!!!!!				!!! Warning that function changing matrix !!! 
	// Parameter:	double array (all matrix value).We will add precision as parametr
	//
	//			!!! Warning that function changing matrix !!! 
	//  
	//************************************
	// double turnMatrix(double **solution);



};

