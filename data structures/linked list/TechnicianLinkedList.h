#ifndef TECHNICIAN_LINKED_LIST_H
#define TECHNICIAN_LINKED_LIST_H

#include "LinkedList.h"
#include "../../classes/person/technician/Technician.h"

class TechnicianNode
{
public:
	TechnicianNode(const Technician& tech);
	~TechnicianNode();

	Technician* getData();
	const Technician* getData() const;
	TechnicianNode* getNext() const;
	void setNext(TechnicianNode* nextNode);

private:
	Technician data;
	TechnicianNode* next;
};

class TechnicianLinkedList : public LinkedList
{
public:
	TechnicianLinkedList();
	TechnicianLinkedList(const TechnicianLinkedList& other);
	TechnicianLinkedList& operator=(const TechnicianLinkedList& other);
	virtual ~TechnicianLinkedList();

	virtual void clear() override;
	void append(const Technician& tech);
	void push_back(const Technician& tech);
	TechnicianNode* getHead() const;

	Technician* findById(int id);
	bool removeById(int id);

private:
	TechnicianNode* head;
	TechnicianNode* tail;
};

#endif
