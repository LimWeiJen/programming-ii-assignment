#ifndef REQUEST_LINKED_LIST_H
#define REQUEST_LINKED_LIST_H

#include "LinkedList.h"
#include "../../classes/request/Request.h"

class RequestNode
{
public:
	RequestNode(const Request& req);
	~RequestNode();

	Request* getData();
	const Request* getData() const;
	RequestNode* getNext() const;
	void setNext(RequestNode* nextNode);

private:
	Request data;
	RequestNode* next;
};

class RequestLinkedList : public LinkedList
{
public:
	RequestLinkedList();
	RequestLinkedList(const RequestLinkedList& other);
	RequestLinkedList& operator=(const RequestLinkedList& other);
	virtual ~RequestLinkedList();

	virtual void clear() override;
	void append(const Request& req);
	void push_back(const Request& req);
	RequestNode* getHead() const;

	Request* findById(int id);
	bool removeById(int id);

private:
	RequestNode* head;
	RequestNode* tail;
};

#endif
