#include "Matrix.h"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////
//																								//
//	to do list																					//
//	1) need to add variant for random values inputing in matrix 								//
//	2) need to add realization for diferent methods	(add Enum, add user interface				//
//	3)exceptions																				//
//	4) copyright																				//
//																								//
//																								//
//																								//
//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	CMatrix *m = new CMatrix;
	int iCols, iRows;
	// user interface
	cout << "Welcome to system analysis calculator 2018" << endl;
	cout << "Please input number of columns in your matrix:";
	cin >> iCols;
	cout << endl; 
	cout << "Please input number of rows in your matrix:";
	cin >> iRows;
	cout << endl;
	m->setSize(iRows, iCols);
	// inputing matrix 
	cin >> *m;
	// Overcharged operator >> 
	/*
		for (size_t col = 0; col < matr.getCols(); ++col)
	{
		std::cout << "Please input collum number" << col << "." << std::endl;
		for (size_t row = 0; row < matr.getRows(); ++row)
		{
			std::cout << "please input value of x[" << row  << "]["<<col << "] " << ":";
			input >> std::to_string(matr[row][col]);
			std::cout << std::endl;
		}
	}
	return input;
	*/

	return 0;
}