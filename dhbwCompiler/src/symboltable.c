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
	if(currentScope!=NULL){
		s->var.scope=currentScope;
		printf("identified a variable \"%s\" in the scope of function \"%s\"\n",s->name,s->var.scope->name);
	}
	else printf("identified a global variable \"%s\"\n",s->name);

	if(currentScope==NULL)
		if(!exists_Sym_glob(name)){
			printf("appending symbol \"%s\" to global symboltable \n",name);
			printf("-----------------------------------------------------------------\n");
			LL_APPEND(symtable,s);
		}
		else return;
	else if(!exists_Sym_loc(name)){
		printf("appending symbol \"%s\" to local table \"%s\" \n",name,currentScope->name);
		printf("-----------------------------------------------------------------\n");
		LL_APPEND(currentScope,s);
	}
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
		printf("-----------------------------------------------------------------\n");
	}

	currentScope = s;
	printf("set current scope to %s\n",currentScope->name);
	printf("-----------------------------------------------------------------\n");

}

void resetScope(){
	currentScope=NULL;
	printf("reset scope to global\n");
	printf("-----------------------------------------------------------------\n");
}

int exists_Sym_glob(char const *name){
	symbol *s = NULL;
	printf("searching for symbol \"%s\" in global table\n",name);
	if(symtable == NULL){
		printf("global symboltable is empty\n");
		return 0;
	}

	LL_FOREACH(symtable,s){
			if (! strcmp(name, s->name)){
				printf("ERROR	--	multiple declaration of variable \"%s\"\n", name);
					return 1;
				}
	}
	printf("cannot find a symbol with the same declaration\n");
	return 0;
}


int exists_Sym_loc(char const *name){
	symbol *s = NULL;
	printf("searching for symbol \"%s\" in table \"%s\"\n",name,currentScope->name);
	if(currentScope->next == NULL){
		printf("local table \"%s\" is empty\n",currentScope->name);
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

	printf("\n\n\t\t - DEBUG ___ SYMBOL _ TABLE ___ DEBUG - \n\n");
	printf("-----------------------------------------------------------------\n");
	printf("     global \t\t|     local\n");
	printf("-----------------------------------------------------------------\n");

	LL_FOREACH(symtable,s)
		if(s->var.scope==NULL)
			printf("|type:%d name:%s| \n",s->type,s->name);
		else
			printf("\t\t\t|type:%d name:%s| \n",s->type,s->name);

//		else
//			printf("|type:int value:%d name:%s scope:%s| \n ",s->var.value,s->name,s->scope->name);

}

