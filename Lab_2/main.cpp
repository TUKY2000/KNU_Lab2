#include "Algorithms.h"
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////// 
// maybe we will input that in other file.
enum Commands { outputMatrix = 1, GaussianElimination, Kachmage, Jakobi, linRegressParametr, finishWork } command;

//************************************
// Function:	convert from inputing char symbol to command type
// Returns:		- 
// Parameter:	-
//************************************
CMatrix (*chooseCmd())(void);

//************************************
// Function:	output all commands
// Returns:		- 
// Parameter:	-
//************************************
void printCommands(const CMatrix & res);

//************************************
// Function:	do command (method) that user have chosen
// Returns:		bool value that means is user still working with program or not
// Parameter:	command, matrix
//************************************
CMatrix & doCommand(CMatrix (*pfunc)(void));


//************************************
// Function:	compare all functions do_co
// Returns:		bool value that means is user still working with program or not
// Parameter:	command, matrix
//************************************
bool AnalysisSimulator();


void printRes(const CMatrix & res);
///////////////////////////////////////////////////////////////////////////////////////////////////// 

void GaussianElimination_(const CMatrix & m);

void JakobiMethod_(const CMatrix & m);

CMatrix gausseMeth();
CMatrix kachmageMeth();
CMatrix jacobiMeth();
CMatrix linealRegr();


int main()
{
	while (AnalysisSimulator())
	{}
	

	system("pause");

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////// 
// maybe we will that input in other files


void GaussianElimination_( CMatrix & m)
{
	CAlgorithms * gaussTest = nullptr;
	gaussTest = new CAlgorithms(m);

	m = (gaussTest->GaussianElimination());
	cout << endl << "ANSWER: (";
	cout << m;
	cout << ")" << endl;
	if (gaussTest != nullptr)	delete gaussTest;

}


CMatrix(*chooseCmd())(void)
{
	int command_ = 0;
	cin >> command_;
	switch (command_)
	{
	case 1: return gausseMeth;		break;
	case 2: return kachmageMeth;	break;
	case 3: return jacobiMeth;		break;
	case 4: return linealRegr;		break;
	default: return nullptr;		break;
	}
}

void printCommands()
{
	cout << "Choose command: " << endl;
	//	cout << "To output matrix press 1" << endl;
	cout << "To calculate by Gaussian elimination press 1" << endl;
	cout << "To calculate by Kachmage method press 2" << endl;
	cout << "To calculate by Jakobi method press 3" << endl;
	cout << "To calculate linear regression press 4" << endl;

}

CMatrix & doCommand(CMatrix (*pfunc)(void))
{
	return (*pfunc)();
}

void printCommands(const CMatrix & res)
{
	cout << "ANSWER: " << res << endl;
}







bool AnalysisSimulator()
{
	printCommands();
	printRes(doCommand(chooseCmd()));
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////// 