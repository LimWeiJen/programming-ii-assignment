#include "LinkedList.h"

LinkedList::LinkedList() : listSize(0) {}

LinkedList::~LinkedList() {}

int LinkedList::size() const
{
	return listSize;
}

bool LinkedList::empty() const
{
	return listSize == 0;
}
