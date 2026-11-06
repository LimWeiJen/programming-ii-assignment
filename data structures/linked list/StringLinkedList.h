#ifndef STRING_LINKED_LIST_H
#define STRING_LINKED_LIST_H

#include "LinkedList.h"
#include <string>

using namespace std;

class StringNode : public Node
{
public:
	StringNode(const string& str);
	virtual ~StringNode();

	string& getData();
	const string& getData() const;
	StringNode* getNext() const;

private:
	string data;
};

class StringLinkedList : public LinkedList
{
public:
	StringLinkedList();
	StringLinkedList(const StringLinkedList& other);
	StringLinkedList& operator=(const StringLinkedList& other);
	virtual ~StringLinkedList();

	void append(const string& str);
	void push_back(const string& str);
	StringNode* getHead() const;

	string getAt(int index) const;
	bool removeAt(int index);
	bool remove(const string& str);
	bool contains(const string& str) const;
};

#endif

