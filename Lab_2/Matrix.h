//
// Created By Ivan Martsilenko and Arthur Onyshkevych
//
//
// All rights reserved
//

#pragma once

#include <ostream>

class CMatrix
{
public:
	CMatrix();
	~CMatrix();

	CMatrix(const CMatrix & other);
	CMatrix(CMatrix && other);
	CMatrix(const unsigned int _rows, const unsigned _cols);
	CMatrix(const unsigned int _rows, const unsigned _cols, const double num);

	void setSize(const unsigned int _rows, const unsigned _cols);

	unsigned int const getRows() const;
	unsigned int const getCols() const;

	CMatrix & operator = (const CMatrix & other);

	bool operator == (const CMatrix & other) const;

	CMatrix operator + (const CMatrix & other);

	CMatrix operator - (const CMatrix & other);

	CMatrix operator * (const CMatrix & other);
	CMatrix operator * (const double & num);

	CMatrix * operator | (const CMatrix & other) const;

	CMatrix operator ~ ();

	friend std::ostream & operator << (std::ostream & output, const CMatrix & matr);
	friend std::istream & operator >> (std::istream & input, CMatrix & matr);

	double	* operator [] (const int & row) const;

	//************************************
	// Function:	input random values in matrix
	// Returns:		-
	// Parameter:	matrix 
	//************************************
	void randomMatrixValues();

	//************************************
	// Function:	Checking if matrix is a symmetrical
	// Returns:		bool value
	// Parameter:	matrix 
	//************************************
	bool isSymmetrical(CMatrix & other);

	//************************************
	// Function:	Checking if matrix is a symmetrical
	// Returns:		bool value
	// Parameter:	matrix 
	//************************************
	CMatrix unitary(const unsigned int & dim);

	//************************************
	// Function:	symmetrically input random values in matrix
	// Returns:		-
	// Parameter:	matrix 
	//************************************
	void symmetricalRandomMatrixValues();

	//************************************
	// Function:  input values in matrix that it creates Gilbert
	// Returns:    -
	// Parameter:  matrix 
	//************************************
	void createGilbertMatrix();

private:

	void create();	//	create massive of pointers-massive of pointers

	void nulify();

	void setElemNum(const double num);

	unsigned int cols
		, rows;


	double * mass;
	CMatrix * redcode;
};