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
symbol *currentScope = NULL;


void pushVar(char const *name) {
	struct symbol *s = NULL;
	s = (struct symbol*)malloc(sizeof(struct symbol));
	s->name = (char *) malloc (strlen (name) + 1);
	s->name = name;
	s->type = 1;
	s->var.scope=currentScope;
	printf("identified a variable %s in the scope %s\n",s->name,s->var.scope->name);
	if(currentScope==NULL)
		if(!exists_Sym_glob(name)){
			printf("appending sym %s to global table \n",name);
			LL_APPEND(symtable,s);
		}
		else return;
	else if(!exists_Sym_loc(name)){
		printf("appending sym %s to local table %s \n",name,currentScope->name);
		LL_APPEND(currentScope,s);
	}
}

void resetScope(){
	currentScope=NULL;
	printf("reset scope to global\n");
}

void pushFunc(int type, char const *name){
	struct symbol *s = NULL;
	s = (struct symbol*)malloc(sizeof(struct symbol));
	s->name = (char *) malloc (strlen (name) + 1);
	s->name = name;
	s->type = type;
	printf("identified function %s of type %d\n",s->name,s->type);

	if(!exists_Sym_glob(name)){
		LL_APPEND(symtable,s);
		printf("appending function %s to global table \n",name);
	}

	currentScope = s;
	printf("set current scope to %s\n",currentScope->name);

}


int exists_Sym_glob(char const *name){
	symbol *s = NULL;
	printf("searching for symbol %s in global table\n",name);
	if(symtable == NULL){
		printf("global symboltable is empty\n");
		return 0;
	}

	LL_FOREACH(symtable,s){
			if (! strcmp(name, s->name)){
				printf("ERROR	--	multiple declaration of variable \"%s\n", name);
					return 1;
				}
	}
	printf("cannot find a symbol with the same declaration\n");
	return 0;
}


int exists_Sym_loc(char const *name){
	symbol *s = NULL;
	printf("searching for symbol %s in table\n",name);
	if(currentScope->next == NULL){
		printf("local table %s is empty\n",currentScope->name);
		return 0;
	}

	LL_FOREACH(currentScope,s){
			if (! strcmp(name, s->name)){
				printf("ERROR	--	multiple declaration of variable \"%s\n", name);
					return 1;
				}
	}
	printf("cannot find a symbol with the same declaration\n");
	return 0;
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

	printf("\n\n - DEBUG __ SYMBOL ___ TABLE - \n\n ");

	LL_FOREACH(symtable,s)
		if(s->var.scope==NULL)
			printf("|type:%d name:%s| \n",s->type,s->name);

//		else
//			printf("|type:int value:%d name:%s scope:%s| \n ",s->var.value,s->name,s->scope->name);

}

