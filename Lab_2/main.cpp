//
// Created By Ivan Martsilenko and Arthur Onyshkevych
//
//
// All rights reserved
//

#include "Algorithms.h"
#include <iostream>
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
// Function:	doing Linaer Regression
// Returns:		-
// Parameter:	matrix
//************************************
void LinRegression_(CMatrix & matr);

int main()
{
	CMatrix *matr = new CMatrix;
	int iCols, iRows;
	// user interface
	cout << "Welcome to system analysis calculator 2018" << endl;
	cout << endl;
	cout << "Please input number of columns in your matrix:";
	cin >> iCols;
	cout << endl; 
	cout << "Please input number of rows in your matrix:";
	cin >> iRows;
	cout << endl;
	matr->setSize(iRows, iCols);

	AnalysisSimulator(*matr);

	if (matr != nullptr)	delete matr;

	system("pause");

	return 0;
}

void GaussianElimination_( CMatrix & matr)
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



bool doCommand(Commands command, CMatrix &matr)
{
	switch (command)
	{
	case outputMatrix:
		cout << matr;
		break;
	case GaussianElimination:
		cin >> matr;
		GaussianElimination_(matr);
		break;
	case Kachmage:
		cin >> matr;
		KachmageMethod_(matr);
		break;
	case  Jakobi:
		cout << "Please prees 1 if you want to randomize matrix values" << endl << 
				" or press 0 if you want to input matrix by your own" << endl;
		int inputType;
		cin >> inputType;
		if (inputType)	matr.symmetricalRandomMatrixValues(matr);
		else	cin >> matr;
		if (matr.isSymmetrical(matr))
		{
			JakobiMethod_(matr);
		}
		else cout << " matrix isn't symmetrical" << endl;
		break;
	case linRegressParametr:
		cin >> matr;
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
	printCommands();
	inputCommand();
	return doCommand(command, matr);
}