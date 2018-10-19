#include "Matrix.h"
#include "Algorithms.h"
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
	cout << *m;
	//	test Gaussian method

	CAlgorithms * gaussTest = nullptr;
	gaussTest = new CAlgorithms(*m);

	std::vector<double> x = gaussTest->GaussianElimination();
	
	for (vector<double>::iterator ITER = x.begin(); ITER < x.end(); ++ITER)
	{
		cout << *ITER << " ";
	}

	if (m != nullptr)	delete m;
	if (gaussTest != nullptr)	delete gaussTest;

	system("pause");
	return 0;
}