#include "Matrix.h"
#include <iostream>

using namespace std;
int main()
{

	CMatrix *m = new CMatrix;
	int iCols, iRows;
	// user interface
	cout << "Welcome to system analysis calculator 2018" << endl;
	cout << "Please input number of collums in your matrix:";
	cin >> iCols;
	cout << endl;
	cout << "Please input number of rows in your matrix:";
	cin >> iRows;
	cout << endl;
	//double num;	
	//	cin >> num;
	m->setSize(iRows, iCols);

	cin >> *m;
	/*for (int i = 0; i < iRows; i++)
	{
		cout << "Please input row number " << i << "." << endl;
		for (int j = 0; j < iCols; j++)
		{
			cout << "please input value of x" << j << ":";
			cin >> num;
			*m[i][j] = num;
		}
	}*/
	return 0;
}