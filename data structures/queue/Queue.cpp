#include "Queue.h"
#include "queue node/QueueNode.h"

Queue::Queue(Request* req) : head(new QueueNode(req)), tail(this->head), queueSize(1) {}

int Queue::size()
{
	return queueSize;
}

Request* Queue::front()
{
	return head->getVal();
}

void Queue::push(Request* val)
{
	queueSize++;
	tail->updateNext(new QueueNode(val));
	tail = tail->getNext();
}

void Queue::pop()
{
	queueSize--;
	QueueNode* tmp = head;
	head = head->getNext();
	delete tmp;
}