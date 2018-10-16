#include "Matrix.h"
#include <iostream>
using namespace std;

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
	//
	cout << endl;
	m->setSize(iRows, iCols);
	cin >> *m;

	return 0;
}