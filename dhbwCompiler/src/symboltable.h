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

void printallfunctions();

#endif


