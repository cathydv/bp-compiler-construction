/*
 * ir_code_generation.c
 *
 *  Created on: Apr 3, 2012
 *      Author: FS
 */

#include "ir_code_generation.h"
#include "symboltable.h"
#include "parser.tab.h"
#include "stdio.h"
#include "stdlib.h"

//temporäre Variablen (5)
struct symbolTemp *irtemp()
{
	char buffer [5];
	struct symbol temp;
	temp = tempSym(buffer);
	return (temp);
}
