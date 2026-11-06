#ifndef TECHNICIAN_LINKED_LIST_H
#define TECHNICIAN_LINKED_LIST_H

#include "LinkedList.h"
#include "../../classes/person/technician/Technician.h"

class TechnicianNode : public Node
{
public:
	TechnicianNode(const Technician& tech);
	virtual ~TechnicianNode();

	Technician* getData();
	const Technician* getData() const;
	TechnicianNode* getNext() const;

private:
	Technician data;
};

class TechnicianLinkedList : public LinkedList
{
public:
	TechnicianLinkedList();
	TechnicianLinkedList(const TechnicianLinkedList& other);
	TechnicianLinkedList& operator=(const TechnicianLinkedList& other);
	virtual ~TechnicianLinkedList();

	void append(const Technician& tech);
	void push_back(const Technician& tech);
	TechnicianNode* getHead() const;

	Technician* findById(int id);
	bool removeById(int id);
};

#endif

