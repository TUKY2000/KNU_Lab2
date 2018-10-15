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
		
	double * operator [] (const int & row) const;


private:	

	void create();	//	create massive of pointers-massive of pointers

	unsigned int cols
		, rows;

	double * matr = nullptr;
};

