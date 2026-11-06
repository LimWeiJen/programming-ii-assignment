#include "Node.h"

Node::Node() : next(nullptr) {}

Node::~Node() {}

Node* Node::getNext() const
{
	return next;
}

void Node::setNext(Node* next)
{
	this->next = next;
}

