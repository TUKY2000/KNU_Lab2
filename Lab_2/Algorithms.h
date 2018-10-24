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

	//void SoLEtoMATR(const std::istream & input);

	//************************************
	// Function:	solve the matrix by Gaussian method
	// Returns:		vector   
	// Parameter:	void
	//************************************
	std::vector<double> GaussianElimination();


	//************************************
	// Function:  Checking if matrix is a symmetrical
	// Returns:    return new massive of own values !!!!! will change that !!!!!!        !!! Warning that function changing matrix !!! 
	// Parameter:  double array (all matrix value).We will add precision as parametr
	//
	//      !!! Warning that function changing matrix !!! 
	//  
	//************************************
	//double JakobiMethod(double);

private:
		
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
	std::pair<unsigned const int, double> findMax(const int & col) const;

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
	// Returns:		return massive of own values !
	// Parameter:	
	//
	//			!!! Warning that function changing matrix !!! 
	//  
	//************************************
	std::vector<double>  JakobiMethod();

	//***************************************************
	// Function:	Searching max element that not on the diag
	// Returns:		---
	// Parameter:	double array (all matrix value)  
	//***************************************************
	void JakobiFindMax(double max, size_t &maxRow, size_t &maxCol);
	
	//***************************************************
	// Function:	prepare Turn matrix for the next iteration
	// Returns:		-
	// Parameter:	 matrix turnMatr, all of them Inicianalizate in bool JakoniMethod(); 
	//***************************************************
	void prepareTurnMatr(size_t maxRow, size_t maxCol, CMatrix &turnMatr);

	//***************************************************
	// Function:	turn matrix 
	// Returns:		-
	// Parameter:	double array (all matrix value)  
	//***************************************************
	void JakobiTurnMatrix( CMatrix &turnMatr);

	//***************************************************
	// Function:	input solution in vector res 
	// Returns:		-
	// Parameter:	double array (all matrix value)  
	//***************************************************
	void JakobiSolution(std::vector<double> res);

};

