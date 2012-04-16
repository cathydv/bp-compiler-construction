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


void pushVar(char const *name) {
	struct symbol *s = NULL;
	s = (struct symbol*)malloc(sizeof(struct symbol));
	s->name = (char *) malloc (strlen (name) + 1);
	s->name = name;
	s->type = 1;
	s->var.value = 12;
	if(!exists_Sym(name))
		LL_APPEND(symtable,s);
}

void pushFunc(int type, char const *name){
	struct symbol *s = NULL;
	s = (struct symbol*)malloc(sizeof(struct symbol));
	s->name = (char *) malloc (strlen (name) + 1);
	s->name = name;
	s->isFunc = 1;
	s->type = type;
	if(!exists_Sym(name))
		LL_APPEND(symtable,s);
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

struct Symbol* find_Sym(char const *name){
	symbol *s = NULL;
	LL_FOREACH(symtable,s)
		if (! strcmp(name, s->name)){
			printf("\n found symbol %s",name);
			return s;
		}
}

void debug_printSymbolTable(){
	symbol *s = NULL;

	printf("\n\n - debug_printAllSymbols - \n\n ");

	LL_FOREACH(symtable,s){
	if(!s->isFunc)
		printf("|type:int value:%d name:%s| \n ",s->var.value,s->name);
	else
		printf("|type:%d name:%s| \n",s->type,s->name);
	}
}

