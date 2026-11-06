#include "TechnicianLinkedList.h"

TechnicianNode::TechnicianNode(const Technician& tech) : Node(), data(tech) {}

TechnicianNode::~TechnicianNode() {}

Technician* TechnicianNode::getData()
{
	return &data;
}

const Technician* TechnicianNode::getData() const
{
	return &data;
}

TechnicianNode* TechnicianNode::getNext() const
{
	return static_cast<TechnicianNode*>(next);
}

TechnicianLinkedList::TechnicianLinkedList() : LinkedList() {}

TechnicianLinkedList::TechnicianLinkedList(const TechnicianLinkedList& other) : LinkedList()
{
	for (TechnicianNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
	{
		append(*(curr->getData()));
	}
}

TechnicianLinkedList& TechnicianLinkedList::operator=(const TechnicianLinkedList& other)
{
	if (this != &other)
	{
		clear();
		for (TechnicianNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
		{
			append(*(curr->getData()));
		}
	}
	return *this;
}

TechnicianLinkedList::~TechnicianLinkedList()
{
	clear();
}

void TechnicianLinkedList::append(const Technician& tech)
{
	TechnicianNode* newNode = new TechnicianNode(tech);
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

void TechnicianLinkedList::push_back(const Technician& tech)
{
	append(tech);
}

TechnicianNode* TechnicianLinkedList::getHead() const
{
	return static_cast<TechnicianNode*>(head);
}

Technician* TechnicianLinkedList::findById(int id)
{
	for (TechnicianNode* curr = getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() == id)
		{
			return curr->getData();
		}
	}
	return nullptr;
}

bool TechnicianLinkedList::removeById(int id)
{
	TechnicianNode* curr = getHead();
	TechnicianNode* prev = nullptr;

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

