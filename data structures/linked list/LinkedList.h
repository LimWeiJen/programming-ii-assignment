#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "changelog/ChangeLog.h"

class LinkedList
{
public:
    LinkedList();
	LinkedList(ChangeLog* val);

	ChangeLog* getVal();
	LinkedList* getNext();
	void updateVal(ChangeLog* val);
	void updateNext(LinkedList* next);

private:
	LinkedList* next;
	ChangeLog* val;
};

#endif