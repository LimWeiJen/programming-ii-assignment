#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

LinkedList::~LinkedList()
{
	clear();
}

int LinkedList::size() const
{
	return listSize;
}

bool LinkedList::empty() const
{
	return listSize == 0;
}

void LinkedList::clear()
{
	Node* current = head;
	while (current != nullptr)
	{
		Node* nextNode = current->getNext();
		delete current;
		current = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	listSize = 0;
}

Node* LinkedList::getHeadNode() const
{
	return head;
}
