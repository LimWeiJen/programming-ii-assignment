#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();

	int size() const;
	bool empty() const;
	virtual void clear();

	Node* getHeadNode() const;

protected:
	Node* head;
	Node* tail;
	int listSize;
};

#endif
