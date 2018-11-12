//
// Created By Ivan Martsilenko and Arthur Onishkevich
//
//
// All rights reserved
//

#pragma once
#include "Matrix.h"
#include <vector>

class CAlgorithms
{
public:
	CAlgorithms();
	~CAlgorithms();

	CAlgorithms(const CMatrix & _matr);

	void downlMatr(const CMatrix & _matr);

	void downlMatr(const int & rows, const int & cols);

	//************************************
	// Function:	solve the matrix by Gaussian method
	// Returns:		CMatrix  
	// Parameter:	void
	//************************************
	CMatrix & GaussianElimination();

	//************************************
	// Function:	Doing all Jakobi method
	// Returns:		return massive of own values !
	// Parameter:	
	//************************************
	CMatrix & JakobiMethod();

	//************************************
	// Function:	find coefficients of the line function 
	// Returns:		CMatrix 
	// Parameter:	void
	//************************************
	CMatrix & LinRegression();

	//************************************
	// Function:	solve the matrix by Kachmage method
	// Returns:		CMatrix  
	// Parameter:	void
	//************************************
	CMatrix & KachmageMethod();

private:

	CMatrix * matr = nullptr;
	CMatrix * original = nullptr;

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
	std::pair<unsigned const int, double> findMax(const int & col) const;

	//************************************
	// Function:	Find max element in column
	// Returns:		number of row where is max element
	// Parameter:	const int & col
	//************************************
	bool nonZeroInCol(const int & col, std::pair<unsigned int, double> & leadEl) const;

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
	void normalize(unsigned const int & row, const double & element);

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
	CMatrix & reverseSubstitution();



	// Jakobi 

	//***************************************************
	// Function:	Searching max element that not on the diagonal
	// Returns:		---
	// Parameter:	double array (all matrix value)  
	//***************************************************
	void JakobiFindMax(double &max, size_t &maxRow, size_t &maxCol);

	//***************************************************
	// Function:	prepare Turn matrix for the next iteration
	// Returns:		-
	// Parameter:	 matrix turnMatr, all of them Inicianalizate in bool JakoniMethod(); 
	//***************************************************
	void prepareTurnMatr(size_t maxRow, size_t maxCol, CMatrix &turnMatr);

	//***************************************************
	// Function:	turn matrix 
	// Returns:		-
	// Parameter:	matrix 
	//***************************************************
	void JakobiTurnMatrix(CMatrix &turnMatr);

	//***************************************************
	// Function:	input solution in vector res 
	// Returns:		matrix (n,1) with result
	// Parameter:	matrix  
	//***************************************************
	CMatrix & JakobiSolution();

	//***************************************************
	// Function:	making Identity matrix
	// Returns:		-
	// Parameter:	matrix  
	//***************************************************
	void makeIdentityMatrix(CMatrix &turnMatr);

	//***************************************************
	// Function:	making all values of matrix = 0
	// Returns:		-
	// Parameter:	matrix  
	//***************************************************
	void makeZeroMatrix(CMatrix &other);

	//***************************************************
	// Function:	calculating fault
	// Returns:		-
	// Parameter:	double fault
	//***************************************************
	void calculateJakobiFault(double & fault);


	//***************************************************
	// Function:	making all values that <precision = 0
	// Returns:		-
	// Parameter:	matrix, precision 
	//***************************************************
	void cleanZeroElements(double precision);



	//	Lineal Regression

	//***************************************************
	// Function:	build the matrix c_ij = summ_(i->M)(y * x_j)
	// Returns:		CMatrix &
	// Parameter:	void 
	//***************************************************
	CMatrix & getFreeMembMatr();

	//***************************************************
	// Function:	build the matrix c_kj = summ_(i->M)(x_k * x_j)
	// Returns:		CMatrix &
	// Parameter:	void
	//***************************************************
	CMatrix & getSumMatr();

	////***************************************************
	//// Function:	generate random pointers that are not far from the function which we need to find
	//// Returns:		CMatrix &
	//// Parameter:	matrix(vector) of coefficients of function
	////***************************************************
	//CMatrix & randPointers(const CMatrix & coeffs);

	// Kachmage

	//***************************************************
	// Function:	calculate the norma of vector
	// Returns:		double
	// Parameter:	matrix(vector) 
	//***************************************************
	double norma(const CMatrix & vect);

	//***************************************************
	// Function:	create matrix(vector) which is one of the rows of the main matrix
	// Returns:		CMatrix &
	// Parameter:	number of row which will be the matrix
	//***************************************************
	CMatrix & getMRow(const unsigned int & row);

	//***************************************************
	// Function:	calculate a skalar of two matrices(vectors)
	// Returns:		double
	// Parameter:	two matrix
	//***************************************************
	double skalar(const CMatrix & A, const CMatrix & B);

	void checkSolution(const CMatrix & result);
};