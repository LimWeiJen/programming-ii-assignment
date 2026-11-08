#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();

	int size() const;
	bool empty() const;
	virtual void clear();

protected:
	int listSize;
};

#endif
