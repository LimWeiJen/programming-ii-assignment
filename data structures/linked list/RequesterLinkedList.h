#ifndef REQUESTER_LINKED_LIST_H
#define REQUESTER_LINKED_LIST_H

#include "LinkedList.h"
#include "../../classes/person/requester/Requester.h"

class RequesterNode : public Node
{
public:
	RequesterNode(const Requester& req);
	virtual ~RequesterNode();

	Requester* getData();
	const Requester* getData() const;
	RequesterNode* getNext() const;

private:
	Requester data;
};

class RequesterLinkedList : public LinkedList
{
public:
	RequesterLinkedList();
	RequesterLinkedList(const RequesterLinkedList& other);
	RequesterLinkedList& operator=(const RequesterLinkedList& other);
	virtual ~RequesterLinkedList();

	void append(const Requester& req);
	void push_back(const Requester& req);
	RequesterNode* getHead() const;

	Requester* findById(int id);
	bool removeById(int id);
};

#endif

