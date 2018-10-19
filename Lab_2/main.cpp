#include "Matrix.h"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////
//																								//
//	to do list																					//
//	1) need to add variant for random values inputing in matrix 	 							//
//	2) need to add realization for diferent methods	(add Enum, add user interface				//
//	3)exceptions																				//
//	4) copyright																				//
//																								//
//																								//
//																								//
//////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////// 
// maybe we will input that in other file.
enum Commands { outputMatrix = 1, GaussianElimination, Kachmage, Jakobi, linRegressParametr, finishWork } command;

//************************************
// Function:	convert from inputing char symbol to commandtype
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
// Function:	do command (method) that user have choosen
// Returns:		bool value that means is user still working with programm or not
// Parameter:	command, matrix
//************************************
bool doCommand(Commands command, CMatrix &matr);

//************************************
// Function:	compare all functions do_co
// Returns:		bool value that means is user still working with programm or not
// Parameter:	command, matrix
//************************************
bool AnalysisSimulator(CMatrix &matr);
///////////////////////////////////////////////////////////////////////////////////////////////////// 

int main()
{
	CMatrix *matr = new CMatrix;
	int iCols, iRows;
	// user interface
	cout << "Welcome to system analysis calculator 2018" << endl;
	cout << "Please choose the method that you want, press \'h\' for help:" ;
	//AnalysisSimulator(	matr); // need to fix that

	cout << endl;
	cout << "Please input number of columns in your matrix:";
	cin >> iCols;
	cout << endl; 
	cout << "Please input number of rows in your matrix:";
	cin >> iRows;
	cout << endl;
	matr->setSize(iRows, iCols);
	// inputing matrix 
	cin >> *matr;
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
	
	system("pause");
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////// 
// maybe we will that input in other files

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

void printCommands()
{
	cout << "Choose command: " << endl;
	cout << "To output matrix press 1" << endl;
	cout << "To calculate by Gaussian elimination press 2" << endl;
	cout << "To calculate by Kachmage method press 3" << endl;
	cout << "To calculate by Jakobi methodpress 4" << endl;
	cout << "To wate some time press 5" << endl;
	cout << "To finish work with system analysis calculator 2018 press 6 " << endl;

}

bool doCommand(Commands command, CMatrix &matr)
{


	switch (command)
	{
	case outputMatrix:
		cout << matr;
		break;
	case GaussianElimination:
		cout << "We will add that function in nearest update" << endl;
		break;
	case Kachmage:
		cout << "We will add that function in nearest update" << endl;
		break;
	case  Jakobi:
		cout << "We will add that function in nearest update" << endl;
		break;
	case linRegressParametr:
		cout << "We will add that function in nearest update" << endl;
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


bool AnalysisSimulator(CMatrix &matr)
{
	printCommands();
	inputCommand();
	return doCommand(command, matr);
}
///////////////////////////////////////////////////////////////////////////////////////////////////// 