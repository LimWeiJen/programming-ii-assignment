#include "RequesterLinkedList.h"

RequesterNode::RequesterNode(const Requester& req) : Node(), data(req) {}

RequesterNode::~RequesterNode() {}

Requester* RequesterNode::getData()
{
	return &data;
}

const Requester* RequesterNode::getData() const
{
	return &data;
}

RequesterNode* RequesterNode::getNext() const
{
	return static_cast<RequesterNode*>(next);
}

RequesterLinkedList::RequesterLinkedList() : LinkedList() {}

RequesterLinkedList::RequesterLinkedList(const RequesterLinkedList& other) : LinkedList()
{
	for (RequesterNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
	{
		append(*(curr->getData()));
	}
}

RequesterLinkedList& RequesterLinkedList::operator=(const RequesterLinkedList& other)
{
	if (this != &other)
	{
		clear();
		for (RequesterNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
		{
			append(*(curr->getData()));
		}
	}
	return *this;
}

RequesterLinkedList::~RequesterLinkedList()
{
	clear();
}

void RequesterLinkedList::append(const Requester& req)
{
	RequesterNode* newNode = new RequesterNode(req);
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

void RequesterLinkedList::push_back(const Requester& req)
{
	append(req);
}

RequesterNode* RequesterLinkedList::getHead() const
{
	return static_cast<RequesterNode*>(head);
}

Requester* RequesterLinkedList::findById(int id)
{
	for (RequesterNode* curr = getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() == id)
		{
			return curr->getData();
		}
	}
	return nullptr;
}

bool RequesterLinkedList::removeById(int id)
{
	RequesterNode* curr = getHead();
	RequesterNode* prev = nullptr;

	while (curr != nullptr)
	{
		if (curr->getData()->getID() == id)
		{
			if (prev == nullptr)
			{
				head = curr->getNext();
				if (head == nullptr) tail = nullptr;
			}
			else
			{
				prev->setNext(curr->getNext());
				if (curr == tail) tail = prev;
			}
			delete curr;
			listSize--;
			return true;
		}
		prev = curr;
		curr = curr->getNext();
	}
	return false;
}

