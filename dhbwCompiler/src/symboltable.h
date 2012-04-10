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

struct func{

};

struct integ{
	int value;

};

typedef struct symbol {
    char *name;
    int type;
    union{
    	struct func;
    	struct integ;
    };
    struct symbol *next;
} symbol;

int exists_Sym(char const *name);

void insert_Sym(int type,char const *name);

struct Symbol* find_Sym();

void debug_printSymbolTable();

void init_table();

#endif


