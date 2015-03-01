//----------------------------------------------------------------------------
// RPNCalcDriver.cpp
//
// functions:  main(void)
//----------------------------------------------------------------------------

#include "RPNCalc.h"
using namespace std;
//----------------------------------------------------------------------------
//
//	Function:	main()
//
//	Title:		Driver for RPN Calculator
//
//	Description:	This file contains function main()
//					which creates and starts an RPN calculator
//
//	Programmer:	Sarah Kazemian
//   
//	Date:		6/5/14
// 
//	Version:	1.01
//  
// Environment: Software:   Microsoft Windows 8 for execution, 
//				   Compiles under Microsoft Visual Studio 2012
// 
//	Calls:		CRPNCalc constructor
// 
//	Returns:	EXIT_SUCCESS  = successful 
//
//	History Log:
//			4/20/14  PB completed version 1.0
//			5/23/14  SK completed version 1.01
//----------------------------------------------------------------------------
int main (void)
{
	
	using SK_CALC::CRPNCalc;
	CRPNCalc calculator;
	cout << endl << "Press \"Enter\" to close program.";
	cin.get();
	cin.get();

	return EXIT_SUCCESS;
}
