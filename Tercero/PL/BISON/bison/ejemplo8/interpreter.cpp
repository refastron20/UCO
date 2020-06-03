/*! 
  \file interpreter.cpp
  \brief Main program
*/

/*!
 \mainpage Flex and Bison: example 8
 \author   
 \date     2018 - 4 - 26
 \version  1.0
 \warning  Grammar with shift - reduce conflict
 
 \attention
 	+ The new assigment rule generates a conflict.
	 \n  stmtlist -> stmtlist asgn SEMICOLON
     \n The assignment can be generated in two ways:
	 \n asgn ==> ID ASSIGNMENT exp
     \n exp ==> asgn ==> ID ASSIGNMENT exp 

 \note
    + The "interpreter.output" file is generated to obtain information about the conflict
      \n "bison -v interpreter.y"
    + The conflict will be corrected in example 9
*/


// New in example 2
#include <stdio.h>
#include <string>
//

#include "./parser/interpreter.tab.h"

int lineNumber = 1; //!< Line counter

// New in example 2
extern FILE * yyin; //!< Standard input device for yylex() 
std::string progname; //!<  Program name
//


//////////////////////////////////////////////
// NEW in example 6 

// Use for recovery of runtime errors 
#include <setjmp.h>
#include <signal.h>

// Error recovery functions 
#include "error/error.hpp"

/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
extern jmp_buf begin; //!<  It enables recovery of runtime errors 

//////////////////////////////////////////////
// NEW in example 7 

#include "table/table.hpp"

lp::Table table; //!< Table of Symbols

//////////////////////////////////////////////

//! \name Main program

/*! 
	\brief  Main function
	\param  argc: number of command line parameters
	\param  argv: values of command line parameters
	\return int
	\note   C++ requires that main returns an int value
	\sa     yyparse, yylex
*/
int main(int argc, char *argv[])
{
 // Option -t needed
 // yydebug = 1;
 
	/*****************************************/
	/* NEW in example 2 */
	/* 
		If the input file exists 
	      then 
    	       it is set as input device for yylex();
		otherwise
            the input device is the keyboard (stdin)
	*/
	if (argc == 2) 
    	 yyin = fopen(argv[1],"r");

	/* Copy the name of the interpreter */
	progname = argv[0];
	/*****************************************/

	/*********************************************************/
	/* NEW in example 6 */ 
	/* Sets a viable state to continue after a runtime error */
	setjmp(begin);

	/* The name of the function to handle floating-point errors is set */
	signal(SIGFPE,fpecatch);
	/*********************************************************/

	/* Parser function */
	yyparse();

	/* End of program */
	return 0;
}


