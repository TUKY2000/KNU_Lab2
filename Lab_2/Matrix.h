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

	CMatrix & operator + (const CMatrix & other);

	CMatrix & operator - (const CMatrix & other);

	CMatrix & operator * (const CMatrix & other);
	CMatrix & operator * (const double & num);

	CMatrix & operator | (const CMatrix & other);

	CMatrix & operator ~ ();

	friend std::ostream & operator << (std::ostream & output, const CMatrix & matr);
	friend std::istream & operator >> (std::istream & input, CMatrix & matr);
		
	double	* operator [] (const int & row) const;

	void randomMatrixValues(CMatrix matr);

	

	//************************************
	// Function:	Checking if matrix is a symmetrical
	// Returns:		bool value
	// Parameter:	matrix 
	//************************************
	bool isSymmetrical(CMatrix & other);

	CMatrix & unitary(const unsigned int & dim);

	void symmetricalRandomMatrixValues(CMatrix &matr); // we are changing matr here

private:	

	void create();	//	create massive of pointers-massive of pointers

	void nulify();

	void setElemNum(const double num);
	
	unsigned int cols
		, rows;

	double * mass = nullptr;
};