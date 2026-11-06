#include "ChangeLogLinkedList.h"

ChangeLogNode::ChangeLogNode(ChangeLog* log) : Node(), data(log) {}

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
	return static_cast<ChangeLogNode*>(next);
}

ChangeLogLinkedList::ChangeLogLinkedList() : LinkedList() {}

ChangeLogLinkedList::ChangeLogLinkedList(const ChangeLogLinkedList& other) : LinkedList()
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
	return static_cast<ChangeLogNode*>(head);
}

