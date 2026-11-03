#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include "../../../classes/request/Request.h"

class QueueNode
{
public:
	QueueNode(Request* val);

	Request* getVal();
	QueueNode* getNext();
	void updateVal(Request* val);
	void updateNext(QueueNode* next);
private:
	QueueNode* next;
	Request* val;
};

#endif