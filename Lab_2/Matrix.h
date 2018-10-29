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

	CMatrix & operator ~ ();

	friend std::ostream & operator << (std::ostream & output, const CMatrix & matr);
	friend std::istream & operator >> (std::istream & input, CMatrix & matr);
		
	double	* operator [] (const int & row) const;
	void randomMatrixValues(CMatrix matr);

	//CMatrix & reverce();
	

	//************************************
	// Function:	Checking if matrix is a symmetrical
	// Returns:		bool value
	// Parameter:	 double array (all matrix value)  
	//************************************
	bool isSymmetrical(CMatrix & other);

	CMatrix & unitary(const unsigned int & dim);

	void symmetricalRandomMatrixValues(CMatrix matr); // we are changing matr here
private:	
	void swap(const int & row1, const int & row2, CMatrix & other);

	void normalize(unsigned const int & row, const double & element, CMatrix & other);

	void dirSub(unsigned int row, CMatrix & other);

	void revSub(CMatrix & other);

	void create();	//	create massive of pointers-massive of pointers

	void nulify();

	bool nonZeroInCol(const int & col, std::pair<unsigned int, double> & leadEl);

	void setElemNum(const double num);
	
	unsigned int cols
		, rows;

	double * mass = nullptr;
};

