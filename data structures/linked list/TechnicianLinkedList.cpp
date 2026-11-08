#include "TechnicianLinkedList.h"

TechnicianNode::TechnicianNode(const Technician& tech) : data(tech), next(nullptr) {}

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
	return next;
}

void TechnicianNode::setNext(TechnicianNode* nextNode)
{
	this->next = nextNode;
}

TechnicianLinkedList::TechnicianLinkedList() : LinkedList(), head(nullptr), tail(nullptr) {}

TechnicianLinkedList::TechnicianLinkedList(const TechnicianLinkedList& other) : LinkedList(), head(nullptr), tail(nullptr)
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

void TechnicianLinkedList::clear()
{
	TechnicianNode* current = head;
	while (current != nullptr)
	{
		TechnicianNode* nextNode = current->getNext();
		delete current;
		current = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	listSize = 0;
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
	return head;
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
	TechnicianNode* curr = head;
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
