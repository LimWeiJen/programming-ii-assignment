#include "StringLinkedList.h"

StringNode::StringNode(const string& str) : data(str), next(nullptr) {}

StringNode::~StringNode() {}

string& StringNode::getData()
{
	return data;
}

const string& StringNode::getData() const
{
	return data;
}

StringNode* StringNode::getNext() const
{
	return next;
}

void StringNode::setNext(StringNode* nextNode)
{
	this->next = nextNode;
}

StringLinkedList::StringLinkedList() : LinkedList(), head(nullptr), tail(nullptr) {}

StringLinkedList::StringLinkedList(const StringLinkedList& other) : LinkedList(), head(nullptr), tail(nullptr)
{
	for (StringNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
	{
		append(curr->getData());
	}
}

StringLinkedList& StringLinkedList::operator=(const StringLinkedList& other)
{
	if (this != &other)
	{
		clear();
		for (StringNode* curr = other.getHead(); curr != nullptr; curr = curr->getNext())
		{
			append(curr->getData());
		}
	}
	return *this;
}

StringLinkedList::~StringLinkedList()
{
	clear();
}

void StringLinkedList::clear()
{
	StringNode* current = head;
	while (current != nullptr)
	{
		StringNode* nextNode = current->getNext();
		delete current;
		current = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	listSize = 0;
}

void StringLinkedList::append(const string& str)
{
	StringNode* newNode = new StringNode(str);
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

void StringLinkedList::push_back(const string& str)
{
	append(str);
}

StringNode* StringLinkedList::getHead() const
{
	return head;
}

string StringLinkedList::getAt(int index) const
{
	if (index < 0 || index >= listSize) return "";
	int count = 0;
	for (StringNode* curr = getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (count == index)
		{
			return curr->getData();
		}
		count++;
	}
	return "";
}

bool StringLinkedList::removeAt(int index)
{
	if (index < 0 || index >= listSize) return false;
	StringNode* curr = head;
	StringNode* prev = nullptr;
	int count = 0;

	while (curr != nullptr)
	{
		if (count == index)
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
		count++;
	}
	return false;
}

bool StringLinkedList::remove(const string& str)
{
	StringNode* curr = head;
	StringNode* prev = nullptr;

	while (curr != nullptr)
	{
		if (curr->getData() == str)
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

bool StringLinkedList::contains(const string& str) const
{
	for (StringNode* curr = getHead(); curr != nullptr; curr = curr->getNext())
	{
		if (curr->getData() == str)
		{
			return true;
		}
	}
	return false;
}
