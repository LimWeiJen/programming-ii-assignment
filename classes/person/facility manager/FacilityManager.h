#ifndef FACILITY_MANAGER_H 
#define FACILITY_MANAGER_H

#include "../Person.h"
#include "../requester/Requester.h"
#include "../technician/Technician.h"
#include "../../request/Request.h"
#include "../../../data structures/queue/Queue.h"
#include "../../../data structures/linked list/changelog/ChangeLog.h"
#include <vector>
#include <string>

using namespace std;

class FacilityManager : public Person
{
public:
	FacilityManager(string name, int id, string email, string password, DataManager* dataManager = nullptr);
	void displayMenu();
	void viewTechnicians();
	void addTechnician();
	void assignTechnician(int technicianId);
	void removeTechnician(int technicianId);
	void reviewLatestRequest();
	void reviewRequests();
	void viewUsers();
	void removeUser();
	void viewAllCampusLocations();
	void addCampusLocation();
	void removeCampusLocation();
	void viewAllProblemCategories();
	void addProblemCategory();
	void removeProblemCategory();
	void viewServiceHistory();

private:
	vector<Technician> getAllTechnicians();
	vector<Request> getAllRequests();
	vector<Requester> getAllRequester();
	Queue* getCurrentRequestQueue();
	vector<ChangeLog*> getServiceHistory();
};

#endif
