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

struct variable{
	int type;
	int isArray;
	int size;
	struct symbol *scope;
};

struct function{
	int returntype;
	int isProto;
	int hasParams;
	struct symbol *local_table;
	struct symbol *param_list;
};

typedef struct symbol {
    char *name;
    int isFunc;
    union{
    	struct variable var;
    	struct function func;
    }is;
    struct symbol *next;
} symbol;


struct symbol *pushVar(char const *name);

struct symbol *pushFunc(int type, char const *name);

struct Symbol* find_Sym(char const *name);

void deleteFunc(char const *name);

void addParam(struct symbol* function,struct symbol* params);

void renameFunc(struct symbol* function,char const *name);

void resetScope();

void debug_printSymbolTable();

void init_table();

#endif


