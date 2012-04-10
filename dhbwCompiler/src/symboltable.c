/*
 * symboltable.c
 *
 *  Created on: Apr 3, 2012
 *      Author: NA
 */

#include "symboltable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/utlist.h"

symbol *symtable = NULL;

int namecmp(symbol *a, char *b) {
    return strcmp(a->name,b);
}

int exists_Sym(char const *name){
	symbol *s = NULL;
	int cnt;
	cnt = 0;
	if(symtable == NULL) return cnt;
	LL_FOREACH(symtable,s)
	if (! strcmp(name, s->name)){
		printf("\nERROR	--	multiple declaration of variable \"%s\"\n",name);
		cnt++;
	}
	return cnt;
}

void insert_Sym(int type,char const *name){
	struct symbol *s = NULL;
	s = (struct symbol*)malloc(sizeof(struct symbol));
	s->name = name;
	s->type = type;
	LL_APPEND(symtable,s);
}

struct Symbol* find_Sym(){

}

void debug_printSymbolTable(){
	symbol *s = NULL;

	printf("\n\n - debug_printAllSymbols - \n\n");
	LL_FOREACH(symtable,s)printf("|%d  %s|\n   |\n   v\n ",s->type,s->name);
}

