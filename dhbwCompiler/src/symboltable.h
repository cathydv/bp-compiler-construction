#ifndef _DHBWCC_SYMBOLTABLE_H
#define _DHBWCC_SYMBOLTABLE_H
/*
 * symboltable.h
 *
 *  Created on: Apr 3, 2012
 *      Author: NA
 */
#include <stdio.h>
#include "include/utlist.h"

typedef union{
	int value;
	struct symbol *scope;
}var;

typedef union{
	int returntype;
}func;

typedef struct symbol {
    char *name;
    int type;
    var var;
    func func;
    struct symbol *next;
} symbol;


void pushVar(char const *name);

void pushFunc(int type, char const *name);

struct Symbol* find_Sym(char const *name);

void resetScope();

void debug_printSymbolTable();

void init_table();

#endif


