#include "RequesterLinkedList.h"

RequesterNode::RequesterNode(const Requester& req) : data(req), next(nullptr) {}

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
	return next;
}

void RequesterNode::setNext(RequesterNode* nextNode)
{
	this->next = nextNode;
}

RequesterLinkedList::RequesterLinkedList() : LinkedList(), head(nullptr), tail(nullptr) {}

RequesterLinkedList::RequesterLinkedList(const RequesterLinkedList& other) : LinkedList(), head(nullptr), tail(nullptr)
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

void RequesterLinkedList::clear()
{
	RequesterNode* current = head;
	while (current != nullptr)
	{
		RequesterNode* nextNode = current->getNext();
		delete current;
		current = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	listSize = 0;
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
	return head;
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
	RequesterNode* curr = head;
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
