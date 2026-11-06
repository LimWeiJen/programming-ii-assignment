#ifndef CHANGE_LOG_LINKED_LIST_H
#define CHANGE_LOG_LINKED_LIST_H

#include "LinkedList.h"
#include "changelog/ChangeLog.h"

class ChangeLogNode : public Node
{
public:
	ChangeLogNode(ChangeLog* log);
	virtual ~ChangeLogNode();

	ChangeLog* getData();
	const ChangeLog* getData() const;
	ChangeLogNode* getNext() const;

private:
	ChangeLog* data;
};

class ChangeLogLinkedList : public LinkedList
{
public:
	ChangeLogLinkedList();
	ChangeLogLinkedList(const ChangeLogLinkedList& other);
	ChangeLogLinkedList& operator=(const ChangeLogLinkedList& other);
	virtual ~ChangeLogLinkedList();

	void append(ChangeLog* log);
	void push_back(ChangeLog* log);
	ChangeLogNode* getHead() const;
};

#endif

