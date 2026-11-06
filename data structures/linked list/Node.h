#ifndef NODE_H
#define NODE_H

class Node
{
public:
	Node();
	virtual ~Node();

	Node* getNext() const;
	void setNext(Node* next);

protected:
	Node* next;
};

#endif

