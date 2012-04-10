#ifndef _DHBWCC_SYMBOLTABLE_H
#define _DHBWCC_SYMBOLTABLE_H
/*
 * symboltable.h
 *
 *  Created on: Apr 3, 2012
 *      Author: NA
 */
#include<stdio.h>

typedef struct symbol {
    char *name;
    int size;
    int isArray;
    int isFunc;
    int isParam;
    struct Symbol *scope;
    struct symbol *next; /* needed for singly- or doubly-linked lists */
} symbol;

int exists_Sym(struct Symbol *Sym);

void insert_Sym(char const *name){
	printf("\n inserting symbol %s \n",name);
}

struct Symbol* find_Sym();

void debug_printSymbolTable(){
	printf("\n\n - debug_printAllSymbols - \n\n");
}

init_table(){
	symbol *head = NULL;
};

#endif


