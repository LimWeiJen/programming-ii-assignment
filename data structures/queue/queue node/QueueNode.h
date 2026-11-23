#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include "../../../classes/request/Request.h"

struct QueueNode
{
	Request* val;
	QueueNode* next;

	QueueNode(Request* val);

	Request* getVal();
	QueueNode* getNext();
	void updateVal(Request* val);
	void updateNext(QueueNode* next);
};

#endif