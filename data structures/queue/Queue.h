#ifndef QUEUE_H
#define QUEUE_H

#include "queue node/QueueNode.h"

class Queue
{
public:
	Queue(Request* head);
	int size();
	Request* front();
	void push(Request* val);
	void pop();

private:
	QueueNode* head;
	QueueNode* tail;
	int queueSize;
};

#endif