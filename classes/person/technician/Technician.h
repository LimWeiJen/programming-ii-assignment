#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "../Person.h"
#include <string>

using namespace std;

class Technician : public Person
{
public:
	Technician(string name, int id, string email, string password, DataManager* dataManager = nullptr);
	void displayMenu();
	void getCurrentAssignedRequests();
	void updateRequestStatus();
	void addRepairNotes();
};

#endif
