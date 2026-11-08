#include "ChangeLogLinkedList.h"

ChangeLogNode::ChangeLogNode(ChangeLog* log) : data(log), next(nullptr) {}

ChangeLogNode::~ChangeLogNode()
{
	if (data != nullptr)
	{
		delete data;
		data = nullptr;
	}
}

ChangeLog* ChangeLogNode::getData()
{
	return data;
}

const ChangeLog* ChangeLogNode::getData() const
{
	return data;
}

ChangeLogNode* ChangeLogNode::getNext() const
{
	return next;
}

void ChangeLogNode::setNext(ChangeLogNode* nextNode)
{
	this->next = nextNode;
}

ChangeLogLinkedList::ChangeLogLinkedList() : LinkedList(), head(nullptr), tail(nullptr) {}

ChangeLogLinkedList::ChangeLogLinkedList(const ChangeLogLinkedList& other) : LinkedList(), head(nullptr), tail(nullptr)
{
	for (ChangeLogNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
	{
		ChangeLog* oldLog = curr->getData();
		if (oldLog != nullptr)
		{
			ChangeLog* newLog = new ChangeLog(oldLog->getDate(), oldLog->getRequestId(), oldLog->getStatus(), oldLog->getRepairNotes());
			append(newLog);
		}
	}
}

ChangeLogLinkedList& ChangeLogLinkedList::operator=(const ChangeLogLinkedList& other)
{
	if (this != &other)
	{
		clear();
		for (ChangeLogNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
		{
			ChangeLog* oldLog = curr->getData();
			if (oldLog != nullptr)
			{
				ChangeLog* newLog = new ChangeLog(oldLog->getDate(), oldLog->getRequestId(), oldLog->getStatus(), oldLog->getRepairNotes());
				append(newLog);
			}
		}
	}
	return *this;
}

ChangeLogLinkedList::~ChangeLogLinkedList()
{
	clear();
}

void ChangeLogLinkedList::clear()
{
	ChangeLogNode* current = head;
	while (current != nullptr)
	{
		ChangeLogNode* nextNode = current->getNext();
		delete current;
		current = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	listSize = 0;
}

void ChangeLogLinkedList::append(ChangeLog* log)
{
	ChangeLogNode* newNode = new ChangeLogNode(log);
	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->setNext(newNode);
		tail = newNode;
	}
	listSize++;
}

void ChangeLogLinkedList::push_back(ChangeLog* log)
{
	append(log);
}

ChangeLogNode* ChangeLogLinkedList::getHead() const
{
	return head;
}
