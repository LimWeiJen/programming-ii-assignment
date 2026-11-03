#include "QueueNode.h"
#include "../../../classes/request/Request.h"

QueueNode::QueueNode(Request* val): val(val) {}

Request* QueueNode::getVal()
{
	return val;
}

QueueNode* QueueNode::getNext()
{
	return next;
}

void QueueNode::updateVal(Request* val)
{
	this->val = val;
}

void QueueNode::updateNext(QueueNode* next)
{
	this->next = next;
}