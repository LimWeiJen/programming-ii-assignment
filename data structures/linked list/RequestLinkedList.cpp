#include "RequestLinkedList.h"

RequestNode::RequestNode(const Request& req) : data(req), next(nullptr) {}

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
	return next;
}

void RequestNode::setNext(RequestNode* nextNode)
{
	this->next = nextNode;
}

RequestLinkedList::RequestLinkedList() : LinkedList(), head(nullptr), tail(nullptr) {}

RequestLinkedList::RequestLinkedList(const RequestLinkedList& other) : LinkedList(), head(nullptr), tail(nullptr)
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

void RequestLinkedList::clear()
{
	RequestNode* current = head;
	while (current != nullptr)
	{
		RequestNode* nextNode = current->getNext();
		delete current;
		current = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	listSize = 0;
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
	return head;
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
	RequestNode* curr = head;
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
