#ifndef STRING_LINKED_LIST_H
#define STRING_LINKED_LIST_H

#include "LinkedList.h"
#include <string>

using namespace std;

class StringNode
{
public:
	StringNode(const string& str);
	~StringNode();

	string& getData();
	const string& getData() const;
	StringNode* getNext() const;
	void setNext(StringNode* nextNode);

private:
	string data;
	StringNode* next;
};

class StringLinkedList : public LinkedList
{
public:
	StringLinkedList();
	StringLinkedList(const StringLinkedList& other);
	StringLinkedList& operator=(const StringLinkedList& other);
	virtual ~StringLinkedList();

	virtual void clear() override;
	void append(const string& str);
	void push_back(const string& str);
	StringNode* getHead() const;

	string getAt(int index) const;
	bool removeAt(int index);
	bool remove(const string& str);
	bool contains(const string& str) const;

private:
	StringNode* head;
	StringNode* tail;
};

#endif
