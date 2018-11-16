#include "Algorithms.h"
#include "string"
#include <iostream>
#include <ctime>

void printRes(const CMatrix * result)
{
	std::cout << std::endl << "Answer :" << *result << std::endl;
}

unsigned int chooseInp(const std::string * str)
{
	std::cout << "Choose way to input matrix: " << std::endl
		<< "1 -> handle" << std::endl
		<< "2 -> rand values" << std::endl
		<< "3 -> symetrical rand values" << std::endl
		<< "4 -> make Gilbert" << std::endl;

	unsigned short way = 0;
	std::cin >> way;
	return way;
}

CMatrix * cinSize()
{
	unsigned int cols = 0, rows = 0;

	std::cout << "Input number of columns of your matrix: ";
	std::cin >> cols;

	std::cout << "Input number of rows of your matrix: ";
	std::cin >> rows;

	CMatrix * res = new CMatrix(rows, cols);
	return res;
}

void cinGilbert(CMatrix * pMatr)
{
	pMatr->createGilbertMatrix();
}

void cinRandSymerical(CMatrix * pMatr)
{
	pMatr->symmetricalRandomMatrixValues();
}

void cinRand(CMatrix * pMatr)
{
	pMatr->randomMatrixValues();
}

void cinHandle(CMatrix * pMatr)
{
	std::cin >> *pMatr;
}

CMatrix * cinMatrix(const std::string pMatrName)
{
	void(*pCinMartix)(CMatrix * res) = nullptr;
	std::cout << "Input matrix [" << *pCinMartix << "]\n";
	CMatrix * res = cinSize();

	switch (chooseInp(&pMatrName))
	{
	case 1: pCinMartix = cinHandle; break;
	case 2: pCinMartix = cinRand; break;
	case 3: pCinMartix = cinRandSymerical; break;
	case 4: pCinMartix = cinGilbert; break;
	default: break;
	}

	pCinMartix(res);
	return res;
}

CMatrix * randPointers()
{
	std::cout << "Enter number of parameters of function: ";
	unsigned int colsnum = 0;
	std::cin >> colsnum;

	CMatrix koefs(1, colsnum, 0);
	std::cout << "Enter parameters of function" << std::endl;
	std::cin >> koefs;
	srand((unsigned int)time(0));
	CMatrix * res = new CMatrix((20 + rand() % 10), koefs.getCols(), 0);

	for (size_t row = 0; row < res->getRows(); ++row)
	{
		for (size_t col = 1; col < res->getCols(); ++col)
		{
			(*res)[row][col] = (1 + rand() % 300) * pow(-1, rand());
			(*res)[row][0] += (*res)[row][col] * koefs[0][col];

		}
		(*res)[row][0] += koefs[0][0];
	}

	return res;
}

CMatrix * cinMatrForLinRegresion()
{
	unsigned int way = 0;
	std::cout << "Choose way to use method of Linear regression: " << std::endl
		<< "1 -> find function by pointers" << std::endl
		<< "2 -> restore function (tou will enter your parameters & programm will generate poinetrs around it)" << std::endl;

	std::cin >> way;

	switch (way)
	{
	case 1: return cinMatrix("Pointers"); break;
	case 2: return randPointers(); break;
	default:
		break;
	}

}

CMatrix linregresion(const CMatrix * pKoefsMatr, const CMatrix * pFreeMembMatr)
{
	CAlgorithms alg;
	return alg.LinRegression(pKoefsMatr);
}

CMatrix jackobi(const CMatrix * pKoefsMatr, const CMatrix * pFreeMembMatr)
{
	CAlgorithms alg;
	return alg.JakobiMethod(pKoefsMatr);
}

CMatrix kachmage(const CMatrix * pKoefsMatr, const CMatrix * pFreeMembMatr)
{
	CAlgorithms alg;
	return alg.KachmageMethod(pKoefsMatr, pFreeMembMatr);

}

CMatrix gauss(const CMatrix * pKoefsMatr, const CMatrix * pFreeMembMatr)
{
	CAlgorithms alg;
	return alg.GaussianElimination(pKoefsMatr, pFreeMembMatr);
}

//	print aviable commands to use
unsigned int infoCmd()
{
	std::cout << "Choose command you want to use(press a number):" << std::endl
		<< "1 -> Gausse method to solve SoLE" << std::endl
		<< "2 -> Kachmage method to solve SoLE" << std::endl
		<< "3 -> Jackobi method to find ... numbers" << std::endl
		<< "4 -> Linear regression to build a function" << std::endl;

	unsigned int num = 0;
	std::cin >> num;

	return num;
}

CMatrix(*returnFunc())(const CMatrix * pKoefsMatr, const CMatrix * pFreeMembMatr)
{
	switch (infoCmd())
	{
	case 1: return gauss; break;
	case 2: return kachmage; break;
	case 3: return jackobi; break;
	case 4: return linregresion; break;
	default: return nullptr; break;
	}
}


int main()
{
	std::cout << std::fixed;
	std::cout.precision(4);

	CMatrix(*pfunc)(const CMatrix * pKoefsMatr, const CMatrix * pFreeMembMatr) = returnFunc();


	const CMatrix * pA = nullptr;
	const CMatrix * pB = nullptr;

	if (pfunc == linregresion)
	{
		pA = cinMatrForLinRegresion();
		std::cout << *pA << std::endl;
	}
	else if (pfunc == jackobi)
	{
		pA = cinMatrix("Symmetrical");
		std::cout << *pA << std::endl;
	}
	else if (pfunc == nullptr)
	{
		std::cout << "Error: pointer to function is nullptr" << std::endl;
	}
	else
	{
		pA = cinMatrix("Coefficients");
		pB = cinMatrix("Free Numbers");
		std::cout << *pA << std::endl << std::endl << *pB;
	}


	if (pfunc != nullptr)
	{
		printRes(&pfunc(pA, pB));
	}

	if (pA != nullptr) delete pA;
	if (pB != nullptr) delete pB;

	system("pause");
	return 0;
}