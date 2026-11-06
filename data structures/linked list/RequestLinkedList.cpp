#include "RequestLinkedList.h"

RequestNode::RequestNode(const Request& req) : Node(), data(req) {}

RequestNode::~RequestNode() {}

Request* RequestNode::getData()
{
	return &data;
}

const Request* RequestNode::getData() const
{
	return &data;
}

RequestNode* RequestNode::getNext() const
{
	return static_cast<RequestNode*>(next);
}

RequestLinkedList::RequestLinkedList() : LinkedList() {}

RequestLinkedList::RequestLinkedList(const RequestLinkedList& other) : LinkedList()
{
	for (RequestNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
	{
		append(*(curr->getData()));
	}
}

RequestLinkedList& RequestLinkedList::operator=(const RequestLinkedList& other)
{
	if (this != &other)
	{
		clear();
		for (RequestNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
		{
			append(*(curr->getData()));
		}
	}
	return *this;
}

RequestLinkedList::~RequestLinkedList()
{
	clear();
}

void RequestLinkedList::append(const Request& req)
{
	RequestNode* newNode = new RequestNode(req);
	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->setNext(newNode);
		tail = newNode;
	}
	listSize++;
}

void RequestLinkedList::push_back(const Request& req)
{
	append(req);
}

RequestNode* RequestLinkedList::getHead() const
{
	return static_cast<RequestNode*>(head);
}

Request* RequestLinkedList::findById(int id)
{
	for (RequestNode* curr = getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData()->getID() == id)
		{
			return curr->getData();
		}
	}
	return nullptr;
}

bool RequestLinkedList::removeById(int id)
{
	RequestNode* curr = getHead();
	RequestNode* prev = nullptr;

	while (curr != nullptr)
	{
		if (curr->getData()->getID() == id)
		{
			if (prev == nullptr)
			{
				head = curr->getNext();
				if (head == nullptr) tail = nullptr;
			}
			else
			{
				prev->setNext(curr->getNext());
				if (curr == tail) tail = prev;
			}
			delete curr;
			listSize--;
			return true;
		}
		prev = curr;
		curr = curr->getNext();
	}
	return false;
}

