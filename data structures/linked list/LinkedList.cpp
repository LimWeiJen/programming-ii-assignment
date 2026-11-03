#include "LinkedList.h"

LinkedList::LinkedList() : next(nullptr), val(nullptr) {}

LinkedList::LinkedList(ChangeLog* val) : next(nullptr), val(val) {}

ChangeLog* LinkedList::getVal()
{
	return val;
}

LinkedList* LinkedList::getNext()
{
	return next;
}

void LinkedList::updateVal(ChangeLog* val)
{
	this->val = val;
}

void LinkedList::updateNext(LinkedList* next)
{
	this->next = next;
}
