#ifndef CHANGE_LOG_LINKED_LIST_H
#define CHANGE_LOG_LINKED_LIST_H

#include "LinkedList.h"
#include "changelog/ChangeLog.h"

class ChangeLogNode
{
public:
	ChangeLogNode(ChangeLog* log);
	~ChangeLogNode();

	ChangeLog* getData();
	const ChangeLog* getData() const;
	ChangeLogNode* getNext() const;
	void setNext(ChangeLogNode* nextNode);

private:
	ChangeLog* data;
	ChangeLogNode* next;
};

class ChangeLogLinkedList : public LinkedList
{
public:
	ChangeLogLinkedList();
	ChangeLogLinkedList(const ChangeLogLinkedList& other);
	ChangeLogLinkedList& operator=(const ChangeLogLinkedList& other);
	virtual ~ChangeLogLinkedList();

	virtual void clear() override;
	void append(ChangeLog* log);
	void push_back(ChangeLog* log);
	ChangeLogNode* getHead() const;

private:
	ChangeLogNode* head;
	ChangeLogNode* tail;
};

#endif
