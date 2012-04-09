#ifndef _DHBWCC_SYMBOLTABLE_H
#define _DHBWCC_SYMBOLTABLE_H
/*
 * symboltable.h
 *
 *  Created on: Apr 3, 2012
 *      Author: NA
 */

struct symbolVar{
	char* name;
	char* returntype;
	int isArray;
	int isParam;
	int isTemp;
	int size;
	int* stackpointer;        //tbd -- offset
	struct symbolFunc* scope; //points to function
	struct symbolVar* next;   //points to next variable
};

struct symbolFunc{
	char* name;
	char* returnType;
	int isPrototype;
	int paramcount;
	struct symbolVar *param;  //points on parameter List
	struct symbolFunc* next;
};

struct symbolFuncParamList{
	struct symbolVar *first;
	int count;
};


int func_exists();
int var_exists();

int push_func();
int push_var();

int pop_func();
int pop_var();

void get

void printallfunctions();
void printallvars();

void init_table();


#endif


