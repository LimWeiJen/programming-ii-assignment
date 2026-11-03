#ifndef REQUESTER_H
#define REQUESTER_H 

#include "../Person.h"
#include <string>

using namespace std;

class Requester : public Person
{
public:
	Requester(string name, int id, string email, string password, DataManager* dataManager = nullptr);
	void displayMenu();
	void submitRequest();
	void viewSubmittedRequests();
	void viewRequestDetails();
	void cancelRequest();
};

#endif
