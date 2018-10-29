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


	//void SoLEtoMATR(const std::istream & input);

	//************************************
	// Function:	solve the matrix by Gaussian method
	// Returns:		CMatrix  
	// Parameter:	void
	//************************************
	CMatrix & GaussianElimination();


	//************************************
	// Function:	find coefficients of the line function ................
	// Returns:		CMatrix 
	// Parameter:	void
	//************************************
	CMatrix & LinRegression();

	//************************************
	// Function:	Doing all Jakobi method
	// Returns:		return massive of own values !
	// Parameter:	
	//************************************
	std::vector<double>  JakobiMethod();
  
private:
		
	CMatrix * matr = nullptr;
	//	std::vector<double> Ai;

	//************************************
	// Function:	reduce the matrix to triangular shape (first part of Gaussian method)
	// Returns:		number of linearly independent equations  
	// Parameter:	void
	//************************************
	void directElimination();

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
	CMatrix reverseSubstitution();



// Jakobi  part

	//***************************************************
	// Function:	Searching max element that not on the diagonal
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
	void JakobiSolution(std::vector<double> & res);

	//	Lineal Regression

	CMatrix & getFreeMembMatr();
		  
	CMatrix & getSumMatr();
	

	double dispRow(const double && row) const;

	double dispRows(const double && row1, const double && row2) const;

	

};



