/*
 * table_dummy.h
 *
 *  Created on: Apr 9, 2012
 *      Author: compiler
 */

#ifndef TABLE_DUMMY_H_
#define TABLE_DUMMY_H_

struct Element{
	char *name;
	int size;
	int isArray;
	int isFunc;
	int isParam;
	struct Element *scope;

struct Element *next;};

int Elem_exists(struct Element *Elem);
void putElem(struct Element *Elem);
struct Element* getElem();
void debug_printAllElems();



#endif /* TABLE_DUMMY_H_ */
