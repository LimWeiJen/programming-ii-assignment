#ifndef REQUEST_LINKED_LIST_H
#define REQUEST_LINKED_LIST_H

#include "LinkedList.h"
#include "../../classes/request/Request.h"

class RequestNode : public Node
{
public:
	RequestNode(const Request& req);
	virtual ~RequestNode();

	Request* getData();
	const Request* getData() const;
	RequestNode* getNext() const;

private:
	Request data;
};

class RequestLinkedList : public LinkedList
{
public:
	RequestLinkedList();
	RequestLinkedList(const RequestLinkedList& other);
	RequestLinkedList& operator=(const RequestLinkedList& other);
	virtual ~RequestLinkedList();

	void append(const Request& req);
	void push_back(const Request& req);
	RequestNode* getHead() const;

	Request* findById(int id);
	bool removeById(int id);
};

#endif

