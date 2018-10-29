#pragma once

#include <ostream>

//added for randomizer ( rand 1(a))
const int m = 1000;
const double n = (double)m;

class CMatrix
{
public:
	CMatrix();
	~CMatrix();

	CMatrix(const CMatrix & other);
	CMatrix(CMatrix && other);
	CMatrix(const unsigned int _rows, const unsigned _cols);
	CMatrix(const unsigned int _rows, const unsigned _cols, const double num);

	void setSize(const unsigned int & _rows, const unsigned & _cols);

	unsigned int const getRows() const;
	unsigned int const getCols() const;

	CMatrix & operator = (const CMatrix & other);

	bool operator == (const CMatrix & other) const;

	CMatrix & operator + (const CMatrix & other);

	CMatrix & operator - (const CMatrix & other);

	CMatrix & operator * (const CMatrix & other);
	CMatrix & operator * (const double & num);

	CMatrix & operator ~ ();

	CMatrix & transport();

	friend std::ostream & operator << (std::ostream & output, const CMatrix & matr);
	friend std::istream & operator >> (std::istream & input, CMatrix & matr);

	double	* operator [] (const int & row) const;
	void randomMatrixValues(CMatrix matr);


	//************************************
	// Function:	Checking if matrix is a symmetrical
	// Returns:		bool value
	// Parameter:	 double array (all matrix value)  
	//************************************
	bool isSymmetrical(CMatrix & other);

	CMatrix & unitary(const unsigned int & dim);

private:

	void create();	//	create massive of pointers-massive of pointers

	void nulify();


	void setElemNum(const double num);

	void symmetricalRandomMatrixValues(CMatrix matr); // we are changing matr here

	bool nonZeroInCol(const int & col, std::pair<unsigned int, double> & leadEl);

	void swap(const int & row1, const int & row2, CMatrix & other);

	void normalize(unsigned const int & row, const double & element, CMatrix & other);

	void dirSub(unsigned int row, CMatrix & other);

	void revSub(CMatrix & other);

	unsigned int cols, rows;

	double * mass = nullptr;
};

