//
// Created By Ivan Martsilenko and Arthur Onyshkevych
//
//
// All rights reserved
//

#include "Algorithms.h"
#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

enum Commands { outputMatrix = 1, GaussianElimination, Kachmage, Jakobi, linRegressParametr, finishWork } command;

//************************************
// Function:	convert from inputing char symbol to command type
// Returns:		- 
// Parameter:	-
//************************************
Commands inputCommand();

//************************************
// Function:	output all commands
// Returns:		- 
// Parameter:	-
//************************************
void printCommands();


//************************************
// Function:	do command (method) that user have chosen
// Returns:		bool value that means is user still working with program or not
// Parameter:	command, matrix
//************************************
bool doCommand(Commands command, CMatrix &matr);

//************************************
// Function:	compare all functions do_co
// Returns:		bool value that means is user still working with program or not
// Parameter:	command, matrix
//************************************
bool AnalysisSimulator(CMatrix &matr);

//************************************
// Function:	doing Gaussian Elimination
// Returns:		-
// Parameter:	matrix
//************************************
void GaussianElimination_(const CMatrix & matr);

//************************************
// Function:	doing Kachmage Method
// Returns:		-
// Parameter:	matrix
//************************************
void KachmageMethod_(CMatrix & matr);

//************************************
// Function:	doing Jakobi Method
// Returns:		-
// Parameter:	matrix
//************************************
void JakobiMethod_(const CMatrix & matr);

//************************************
// Function:	doing Linear Regression
// Returns:		-
// Parameter:	matrix
//************************************
void LinRegression_(CMatrix & matr);

int main()
{
	cout << fixed;

	cout.precision(5);

	CMatrix *matr = new CMatrix;
	cout << "Welcome to system analysis calculator 2018" << endl;
	AnalysisSimulator(*matr);

	if (matr != nullptr)	delete matr;

	system("pause");

	return 0;
}

void GaussianElimination_(CMatrix & matr)
{
	CAlgorithms * gaussTest = nullptr;
	gaussTest = new CAlgorithms(matr);

	matr = (gaussTest->GaussianElimination());
	cout << endl << "ANSWER: (";
	cout << matr;
	cout << ")" << endl;
	if (gaussTest != nullptr)	delete gaussTest;
}
void KachmageMethod_(CMatrix & matr)
{
	CAlgorithms * newAlg = new CAlgorithms(matr);
	matr = (newAlg->KachmageMethod());
	cout << endl << "ANSWER: (";
	cout << matr;
	cout << ")" << endl;
	if (newAlg != nullptr)	delete newAlg;
}
void JakobiMethod_(CMatrix & matr)
{
	CAlgorithms * JakobiMethod = nullptr;
	JakobiMethod = new CAlgorithms(matr);
	matr = (JakobiMethod->JakobiMethod());
	cout << endl << "ANSWER: (";
	cout << matr;
	cout << ")" << endl;
	if (JakobiMethod != nullptr)	delete JakobiMethod;
}
void LinRegression_(CMatrix & matr)
{
	CAlgorithms * newAlg = new CAlgorithms(matr);
	matr = (newAlg->LinRegression());
	cout << endl << "ANSWER: (";
	cout << matr;
	cout << ")" << endl;
	if (newAlg != nullptr)	delete newAlg;
}

Commands inputCommand()
{
	int command_ = 0;
	cin >> command_;
	switch (command_)
	{
	case 1:
		command = outputMatrix;
		break;
	case 2:
		command = GaussianElimination;
		break;
	case 3:
		command = Kachmage;
		break;
	case 4:
		command = Jakobi;
		break;
	case 5:
		command = linRegressParametr;
		break;
	case 6:
		command = finishWork;
		break;
	default:
		cout << "Wrong command." << endl;
		break;
	}
	return command;
}

CMatrix randPointers()
{
	cout << "Enter number of parameters of function: ";
	unsigned int colsnum = 0;
	cin >> colsnum;

	CMatrix koefs(1, colsnum, 0);
	cout << "Enter parameters of function" << endl;
	cin >> koefs;
	srand(time(0));
	CMatrix res((20 + rand() % 10), koefs.getCols(), 0);

	for (int row = 0; row < res.getRows(); ++row)
	{
		for (int col = 1; col < res.getCols(); ++col)
		{
			(res)[row][col] = (1 + rand() % 300) * pow(-1, rand());
			(res)[row][0] += (res)[row][col] * koefs[0][col];

		}
		(res)[row][0] += koefs[0][0];
		(res)[row][0] += ((rand() % 5)) * pow(-1, rand());
		
	}

	return res;
}

void inputMatrForLin(CMatrix &matr)
{
	cout << "Please press 1 if you want to input function" << endl <<
		"Please press 2 if you want to input values" << endl;
	int inputType;
	cin >> inputType;
	if (inputType == 1) matr = randPointers();
	else if (inputType == 2)  cin >> matr;

	cout << "\n" << "Your matrix :\n" << matr << "\n\n" << endl;
}

void inputMatr(CMatrix &matr)
{
	cout << "Please press 1 if you want to randomize matrix values" << endl <<
		"Please press 2 if you want to symmetrically randomize matrix values" << endl <<
		"Please press 3 if you want to create gilbert type matrix" << endl <<
		" or press 4 if you want to input matrix by your own" << endl;
	int inputType;
	cin >> inputType;
	if (inputType == 1) matr.randomMatrixValues();
	else if (inputType == 2)  matr.symmetricalRandomMatrixValues();
	else if (inputType == 3)  matr.createGilbertMatrix();
	else if (inputType == 4)  cin >> matr;
	else cout << "Wrong command" << endl;

	cout << matr << endl;
}

bool doCommand(Commands command, CMatrix &matr)
{
	switch (command)
	{
	case outputMatrix:
		inputMatr(matr);
		cout << matr;
		cout << endl;
		break;
	case GaussianElimination:
		inputMatr(matr);
		GaussianElimination_(matr);
		break;
	case Kachmage:
		inputMatr(matr);
		KachmageMethod_(matr);
		break;
	case  Jakobi:
		inputMatr(matr);
		if (matr.isSymmetrical(matr))
		{
			JakobiMethod_(matr);
		}
		else cout << " matrix isn't symmetrical" << endl;
		break;
	case linRegressParametr:
		inputMatrForLin(matr);
		LinRegression_(matr);
		break;
	case finishWork:
		cout << "Work was ended." << endl;
		return false;
		break;
	default:

		break;
	}

	return command;
}



void printCommands()
{
	cout << "Choose command: " << endl;
	cout << "To output matrix press 1" << endl;
	cout << "To calculate by Gaussian elimination press 2" << endl;
	cout << "To calculate by Kachmage method press 3" << endl;
	cout << "To calculate by Jakobi method press 4" << endl;
	cout << "To calculate linear regression press 5" << endl;
	cout << "To finish work with system analysis calculator 2018 press 6 " << endl;
}

bool AnalysisSimulator(CMatrix &matr)
{
	int iCols, iRows;
	printCommands();
	inputCommand();
	
	cout << endl;
	cout << "Please input number of columns in your matrix:";
	cin >> iCols;
	cout << endl;
	cout << "Please input number of rows in your matrix:";
	cin >> iRows;
	cout << endl;
	matr.setSize(iRows, iCols);

	return doCommand(command, matr);
}

