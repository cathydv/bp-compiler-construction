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

symbol *exists_Sym_glob(char const *name) {
	symbol *s = NULL;
	printf("searching for symbol \"%s\" in global table\n", name);
	if (symtable == NULL) {
		printf("global symboltable is empty\n");
		return NULL;
	}

	LL_FOREACH(symtable,s) {
		if (!strcmp(name, s->name)) {
			printf("declaration of symbol \"%s\" found\n", name);
			return s;
		}
	}
	printf("cannot find a symbol with the same declaration\n");
	return NULL;
}

symbol * exists_Sym_loc(char const *name) {
	symbol *s = NULL;
	printf("searching for symbol \"%s\" in table %s\n", name,
			currentScope->name);
	if (currentScope->is.func.local_table == NULL) {
		printf("local table is empty\n");
		return NULL;
	}

	LL_FOREACH(currentScope->is.func.local_table,s) {
		if (!strcmp(name, s->name)) {
			printf("ERROR	--	multiple declaration of variable \"%s\n", name);
			return s;
		}
	}

	printf("cannot find a symbol with the same declaration\n");
	return NULL;;
}

void deleteFunc(char const *name) {
	struct symbol *ref = NULL;
	struct symbol *del = NULL;
	ref = exists_Sym_glob(name);

	if (ref != NULL) {
		printf("deleting function %s\n", ref->name);
		LL_DELETE(symtable, ref);
	}

//	if (ref != NULL) {
//		LL_DELETE(ref->is.func.local_table, del);
//		printf("deleting local table of function %s\n", ref->name);
//		LL_DELETE(ref->is.func.param_list, del);
//		printf("deleting param list of function %s\n", ref->name);
//		printf("deleting function %s\n", ref->name);
//		LL_DELETE(symtable, del);
//
//	}

}

struct symbol *pushVar(char const *name) {
	struct symbol *s = NULL;
	s = (struct symbol*) malloc(sizeof(struct symbol));
	s->name = (char *) malloc(strlen(name) + 1);
	s->name = name;
	s->isFunc = 0; //s is not a function
	s->is.var.type = 1; //s is of type int
	s->is.var.isArray = 0; //s is initialized as normal variable
	s->is.var.size = 0; //therefore we have no size

	if (currentScope == NULL) {
		if (exists_Sym_glob(name) == NULL) {
			s->is.var.scope = NULL;
			printf("appending global variable %s\n", name);
			LL_APPEND(symtable, s);
			return s;
		}
	} else if (exists_Sym_loc(name) == NULL) {
		s->is.var.scope = currentScope;
		printf("appending local variable %s to function %s\n", name,
				currentScope->name);
		LL_APPEND(currentScope->is.func.local_table, s);
		return s;
	}

}

struct symbol * pushFunc(int type, char const *name) {
	struct symbol *s = NULL;
	struct symbol *ref = NULL;
	s = (struct symbol*) malloc(sizeof(struct symbol));
	s->name = (char *) malloc(strlen(name) + 1);
	s->name = name;
	s->isFunc = 1;
	s->is.func.returntype = type;
	s->is.func.isProto = 0;
//	printf("identified function %s of type %d\n", s->name,
//			s->is.func.returntype);

	ref = exists_Sym_glob(name);

	if (ref == NULL) {
		LL_APPEND(symtable, s);
		printf("appending function %s to global table \n", name);
		printf(
				"-----------------------------------------------------------------\n");
		currentScope = s;
		printf("set current scope to %s\n", currentScope->name);
		printf(
				"-----------------------------------------------------------------\n");
		return s;
	} else if (ref->is.func.isProto) {
		printf("found proto %s\n", ref->name);
		ref->is.func.isProto = 0;
		currentScope = ref;
		printf("set current scope to %s\n", currentScope->name);
		printf(
				"-----------------------------------------------------------------\n");
		return ref;
	} else
		printf("omgomgomg\n");

	return s;

}

void resetScope() {
	currentScope = NULL;
	printf("reset scope to global\n");
	printf(
			"-----------------------------------------------------------------\n");
}

void addParam(struct symbol* function, struct symbol* params) {
	struct symbol *el;
	struct symbol *currentScope;
	int cnt;
	int i;
	cnt = 0;
	currentScope = function;
	printf("function %s\n",currentScope->name);
	LL_FOREACH(params,el){
		printf("param is %s\n",el->name);
		cnt = cnt+1;
	}

	LL_CONCAT(currentScope->is.func.param_list,params);
	printf("%s\n",currentScope->is.func.param_list->next->next->name);
		//printf("first para is %s", currentScope->is.func.param_list->name);
//	LL_FOREACH(params,el) {
//		printf("adding param %s to function %s\n", el->name, function->name);
//		LL_APPEND(function->is.func.param_list, el);
//	}
//	LL_FOREACH(function->is.func.param_list,el){
//		printf("appended %s\n",el->name);
//	}

}

void renameFunc(struct symbol* function, char const *name) {
	function->name = (char *) malloc(strlen(name) + 1);
	function->name = name;
}

//struct Symbol* find_Sym(char const *name){
//	symbol *s = NULL;
//	LL_FOREACH(symtable,s)
//		if (! strcmp(name, s->name)){
//			printf("\n found symbol %s",name);
//			return s;
//		}
//}

void debug_printSymbolTable() {
	symbol *s = NULL;
	symbol *el = NULL;
	symbol *p = NULL;

	printf("\n\n\t\t - DEBUG ___ SYMBOL _ TABLE ___ DEBUG - \n\n");
	printf(
			"-----------------------------------------------------------------\n");
	printf("     global \t\t|     local\t\t\tparam\n");
	printf(
			"-----------------------------------------------------------------\n");

	LL_FOREACH(symtable,s) {

		// is function
		if (s->isFunc) {
			if (s->is.func.isProto)
				printf("isProto"); // is prototype

			if (s->is.func.returntype) //select returntype
				printf("|int name:%s| \n", s->name);
			else
				printf("|void name:%s| \n", s->name);

			LL_FOREACH(s->is.func.local_table,el) {
				if (el->is.var.isArray)
					printf("\t\t\t|int name:%s[%d] |\n", el->name, // local array
							el->is.var.size);
				else
					printf("\t\t\t|int name:%s| \n", el->name); //local var
			}

			if (s->is.func.hasParams) {
				LL_FOREACH(s->is.func.param_list,el)
					printf("\t\t\t\t\t\t|int name:%s|\n", el->name);
				}
		}

		//is global variable
		else {
			if (s->is.var.isArray)
				printf("|int name:%s[%d] |\n", s->name, s->is.var.size);
			else
				printf("|int name:%s| \n", s->name); //global var

		}
	}
}

